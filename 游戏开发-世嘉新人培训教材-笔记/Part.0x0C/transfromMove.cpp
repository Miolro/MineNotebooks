#include "GameLib/Framework.h"
#include "GameLib/Math.h"
#include <fstream>
/*--------------------------------------------*/ // File
class File
{
public:
	File(const char*);
	~File();
	unsigned getEndia(int position);
private:

	unsigned char* mFileByte;
};
File::File(const char* fileName)
{
	std::ifstream imageFileBuffer(fileName, std::ios::binary);
	imageFileBuffer.seekg(0, std::ios::end);
	int fileSize = imageFileBuffer.tellg();
	imageFileBuffer.seekg(0, std::ios::beg);
	char* originFileByte = new char[fileSize];
	imageFileBuffer.read(originFileByte, fileSize);
	mFileByte = reinterpret_cast<unsigned char*>(originFileByte); // 指针指向originFile 只需要回收一个即可
}
File::~File()
{
	SAFE_DELETE_ARRAY(mFileByte);
}
unsigned File::getEndia(int position)
{
	return mFileByte[position] | mFileByte[position + 1] << 8 | mFileByte[position + 2] << 2 * 8 | mFileByte[position + 3] << 3 * 8;
}
/*--------------------------------------------*/ // Image
class Image
{
public:
	Image(const char*);
	~Image();
	int iWidth();
	int iHeight();
	unsigned pixel(int x, int y);
private:
	int mWidth;
	int mHeight;
	unsigned* mPiexlInfo;
};
Image::Image(const char* fileName)
{
	File file(fileName);
	mHeight = file.getEndia(0x0c);
	mWidth = file.getEndia(0x10);
	mPiexlInfo = new unsigned[mHeight * mWidth];
	for (int i = 0; i < mHeight * mWidth; i++)
	{
		mPiexlInfo[i] = file.getEndia(i * 4 + 0x80);
	}
}
Image::~Image()
{
	SAFE_DELETE_ARRAY(mPiexlInfo);
}
int Image::iWidth()
{
	return mWidth;
}
int Image::iHeight()
{
	return mHeight;
}
unsigned Image::pixel(int x, int y)
{
	return mPiexlInfo[y * mWidth + x];
}
/*--------------------------------------------*/ // Vector
class Vector2
{
public:
	Vector2(); // 空向量
	Vector2(int x, int y); // 带有值的初始化向量 int
	Vector2(double x, double y);
	~Vector2();

	void operator *= (double in);
	void operator+=(const Vector2&); // 向量加法
	void operator-=(const Vector2&);	// 向量减法
	void operator=(const Vector2&);	// 向量复制
	void setInterpolation(Vector2& a, const Vector2& ab, double absize, const Vector2& ac, double acsize);// 向量补间
	//向量 
	double x;
	double y;
};
Vector2::Vector2() :x(0), y(0) {}
Vector2::Vector2(int ix, int iy)
{
	x = static_cast<double>(ix);
	y = static_cast<double>(iy);
};
Vector2::Vector2(double ix, double iy) :x(ix), y(iy) {}
Vector2::~Vector2() {}
void Vector2::operator*=(double in)
{
	x *= in;	y *= in;
}
void Vector2::operator+=(const Vector2& thatVector)
{
	x += thatVector.x;
	y += thatVector.y;
}
void Vector2::operator-=(const Vector2& thatVector)
{
	x -= thatVector.x;
	y -= thatVector.y;
}
void Vector2::operator=(const Vector2& thatVector)
{
	x = thatVector.x;
	y = thatVector.y;
}
void Vector2::setInterpolation(Vector2& a, const Vector2& ab, double absize, const Vector2& ac, double acsize)
{
	//公式 p向量 = a向量+absize1单位的比例*ab向量+ac向量*acsize1单位比例
	*this += a;
	Vector2 tmp;
	tmp = ab;
	tmp *= absize;
	*this += tmp;
	tmp = ac;
	tmp *= acsize;
	*this += tmp;
};

/*--------------------------------------------*/ // Matrix
class Matrix22  // 2*2的矩阵
{
public:
	Matrix22(double im00, double im01, double im10, double im11);
	~Matrix22();
	void multiply(Vector2* out, const Vector2& in)const;

	double m00, m01, m10, m11;
private:

};

Matrix22::Matrix22(double im00, double im01, double im10, double im11) :
	m00(im00), m01(im01), m10(im10), m11(im11)
{
}
Matrix22::~Matrix22() {}
void Matrix22::multiply(Vector2* out, const Vector2& in)const
{
	double tempx = in.x;
	double tempy = in.y;

	out->x = tempx * m00 + tempy * m01;
	out->y = tempx * m10 + tempy * m11;
}

class Matrix23
{
public:
	Matrix23();
	Matrix23(double im00, double im01, double im02, double im10, double im11, double im12);
	~Matrix23();

	double m00; double m01; double m02;
	double m10; double m11; double m12;
};

Matrix23::Matrix23(double im00, double im01, double im02, double im10, double im11, double im12) :
	m00(im00), m01(im01), m02(im02), m10(im10), m11(im11), m12(im12) {}
Matrix23::~Matrix23() {}

/*--------------------------------------------*/ // MainLoop
namespace GameLib
{
	int round(double a)
	{
		a += (a > 0.0) ? 0.5 : -0.5f;
		return static_cast<int>(a);
	}
	// 输出点  输入点  偏移（中心点) 变化矩阵
	void transformPosition(Vector2* oVector, const Vector2& iVector, const Vector2& offset, const Matrix22 matrix)
	{
		//初始化outVector 使用operator=来深拷贝数值
		*oVector = iVector;
		// 偏移到圆心
		*oVector -= offset;
		// 矩阵相乘
		matrix.multiply(oVector, *oVector);
		// 还原图像
		*oVector += offset;
	}
	// 输出点  输入点  
	void transformMove(Vector2* oVector, const Vector2& iVector, const Matrix23 matrix)
	{
		// 使用矩阵对向量做移动操作
		oVector->x = matrix.m00 * iVector.x + matrix.m01 * iVector.y + matrix.m02 * 1;
		oVector->y = matrix.m10 * iVector.x + matrix.m11 * iVector.y + matrix.m12 * 1;
	}
	bool init = true;
	unsigned* vram;
	int gCount = 0;
	int gImageWidth;
	int gImageHeight;
	unsigned* gImagePixel;
	double scaling = 1;
	Vector2 offset(0, 0);
	int direction = +1;
	void Framework::update() {
		if (init) {
			init = false;
			vram = videoMemory();
			Image image("C:/programCode/GameLib/src/03_2DGraphics2/displayImage/bar.dds");
			gImageHeight = image.iHeight();
			gImageWidth = image.iWidth();
			gImagePixel = new unsigned[gImageHeight * gImageWidth];
			for (int y = 0; y < gImageHeight; y++)
			{
				for (int x = 0; x < gImageWidth; x++)
				{
					gImagePixel[y * gImageWidth + x] = image.pixel(x, y);
					//vram[y * width() + x] = image.pixel(x, y);
				}
			}
			// 设置  右上角的点  左上角的点  左下角的点

		}

		// 左上角的顶点
		Vector2 topLeftPoint(10.0, 10.0);
		// 右上角的顶点
		Vector2 topRightPoint = topLeftPoint;
		topRightPoint += Vector2(gImageWidth, 0);
		// 左下角的顶点
		Vector2 bottomLeftPoint = topLeftPoint;
		bottomLeftPoint += Vector2(0, gImageHeight);

		//图像移动
		Vector2 aftMoveTLP(0, 0);
		Vector2 aftMoveTRP(0, 0);
		Vector2 aftMoveBLP(0, 0);
		Matrix23 matrix23(1.0, 0, gCount, 0, 1.0, 0);
		transformMove(&aftMoveTLP, topLeftPoint, matrix23);
		transformMove(&aftMoveTRP, topRightPoint, matrix23);
		transformMove(&aftMoveBLP, bottomLeftPoint, matrix23);

		Vector2 vectorTLPToTRP = aftMoveTRP;
		Vector2 vectorTLPToBLP = aftMoveBLP;

		vectorTLPToTRP -= aftMoveTLP;
		vectorTLPToBLP -= aftMoveTLP;


		for (int y = 0; y < gImageHeight; y++)
		{
			for (int x = 0; x < gImageWidth; x++)
			{
				//计算补间
				double tweeningP1 = static_cast<double>(x) / gImageWidth;
				double tweeningP2 = static_cast<double>(y) / gImageHeight;

				Vector2 p;
				p.setInterpolation(aftMoveTLP, vectorTLPToTRP, tweeningP1, vectorTLPToBLP, tweeningP2);
				int tx = round(p.x);
				int ty = round(p.y);
				vram[ty * width() + tx] = gImagePixel[y * gImageWidth + x];
			}
		}
		gCount += direction;
		if (gCount + gImageWidth > width())
		{
			direction = -1;
		}
		else if (gCount < 0)
		{
			direction = 1;
		}
	}
}