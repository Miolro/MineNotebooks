# 第十二章 旋转缩放平移

## 12.1 旋转

笔者开头点破:双层for循环无法实现角度旋转

所以需要计算每个像素在旋转后应该在哪个位置

流程遍历像素点,对象前像素点做计算,得到计算的值对vram进行对应位置放置像素点

### 12.1.1 旋转坐标的简单方法

|--|--|--|--|
|--|--|--|--|
|`0,0`|0,1|0,2|0,3|
|1,0|1,1|1,2|1,3|
|2,0|2,1|2,2|2,3|
|3,0|3,1|3,2|`3,3`|

图中`0,0`和`3,3`

像素中心坐标`0,0` : `0.5,0.5`
像素中心坐标`3,3` : `3.5,3.5`

### 12.1.2 三角函数

画图画不出来公式敲出来感觉也没什么用不如看书

$a = f(θ)$ 求对边
$b = g(θ)$ 求邻边

θ表示角与他相对的叫对边,与θ相邻的叫邻边

$sin(θ)$ 通过角度求出`对边`的值 (sine)
$cos(θ)$ 通过角度求出`邻边`的值 (cosine)

他们所得的只是边与`斜边一单位`长度的比例 **不是真实长度**

$θ(0°,180°)$但又因为三角形内角和不会超过$180°$如果是直角三角形那么还要再减去$90°$,所以另外两个角不可能超过$90°$

**概念抽离**

原点坐标($0°$)

个人理解

`当θ为0时对边和斜边相当于重合了所以sin的单位长度是0,因为重合的缘故邻边的长度=斜边的长度单位长度是1`(从这里可以知道为什么$sin$在$0°$时候是0,$cos$在$0°$时是1)
`使用sine可以求出纵坐标`
`使用cosine可以求出横坐标`

**正弦和余弦的关系** 

书中图里显示的

$\because sin(x) = cos(y)$
$\because con(x) = sin(y)$
$\because 直角三角形=90°$

$\therefore x + y = 90°$

$\therefore x = 90° - y$
$\therefore y = 90° - x$

带入到
$\because sin(x) = con(y)$
$\therefore sin(x) = cos(90°-x)$
$\therefore cos(x) = sin(90°-x)$

`90°加减角可以做到sin和cos的相互转化`

**泰勒展开**

用像素画一个圆形

```C++
#include "GameLib/Framework.h"
#include "GameLib/Math.h"
namespace GameLib
{
	bool init = false;
	unsigned* vram;
	int round(float num)
	{
		int result = num;
		if (num > 0)
		{
			result = num + 0.5;
		}
		else
		{
			result = num - 0.5;
		}
		return result;
	}

	void Framework::update()
	{
		int centerX = 60;  // 圆心横坐标
		int centerY = 60;  // 圆心纵坐标

		int radius = 30;   // 半径

		if (!init)
		{
			vram = videoMemory();
			init = true;
		}
		float x = 0.0f;
		float y = 0.0f;
        // 360 是画出来的角度 0 是起始角度
		for (int rad = 0; rad < 360; rad++)
		{
			x = sin(rad);
			y = cos(rad);
			int oy = round(radius * y + centerX);
			int ox = round(radius * x + centerY);
			vram[oy * width() + ox] = 0xFFFFFFFF;
		}
	}
}

```

**图片顺时针旋转**

```C++
#include "GameLib/Framework.h"
#include "GameLib/Math.h"
#include <fstream>
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

namespace GameLib
{
	int round(double a)
	{
		a += (a > 0.0) ? 0.5 : -0.5f;
		return static_cast<int>(a);
	}
	void transformPosition(int* oX, int* oY, int iX, int iY, double offsetX, double offsetY, double radius)
	{
		double dX = static_cast<double>(iX);
		double dY = static_cast<double>(iY);

		dX += 0.5f;
		dY += 0.5f;
		// 你可以脑补到一个图片向左向上移动他的坐标
		// 此时的图像以左上角为原点
		// 如果不这样做那么他会把整个图片绕着屏幕左上角的点旋转和大风车一样
		dX -= offsetX;
		dY -= offsetY;
		// 求出那个坐标距离原点的距离  勾股定理很好理解
		double r = sqrt(dX * dX + dY * dY);
		// 然后是角度  使用反向tan 给出两条边求出角度
		double angle = atan2(dY, dX);
		// 原角度radius和angle偏移角度相加
		angle += radius;
		// 变化后的角度求出x和y与斜边比例
		double sine = sin(angle);		// y
		double cosine = cos(angle);		// x
		// 乘比例得到最后xy坐标
		dX = r * cosine;
		dY = r * sine;
		// 将图片位置还原
		dX += offsetX;
		dY += offsetY;
		dX -= 0.5f;
		dY -= 0.5f;
		*oX = round(dX);
		*oY = round(dY);
	}

	bool init = true;
	unsigned* vram;
	int gCount = 0;
	Image* gImage;
	void Framework::update() {
		if (init) {
			gImage = new Image("E:/environment/GameLib/src/03_2DGraphics2/displayImage/bar.dds");
			init = false;
		}
		unsigned* vram = videoMemory();
		int ww = width(); //window width
		int wh = height(); //window height
		//全黑
		for (int i = 0; i < ww * wh; ++i) {
			vram[i] = 0;
		}
		int iw = gImage->iWidth(); //image width
		int ih = gImage->iHeight(); //image height
		double offsetX = static_cast<double>(iw) / 2.0;
		double offsetY = static_cast<double>(ih) / 2.0;

		double rotation = static_cast<double>(gCount);
		for (int y = 0; y < ih; ++y) {
			for (int x = 0; x < iw; ++x) {
				//计算轮换目的地
				int rx, ry;
				transformPosition(&rx, &ry, x, y, offsetX, offsetY, rotation);
				//如果在范围内则粘贴
				if (rx >= 0 && rx < ww && ry >= 0 && ry < wh) {
					vram[ry * ww + rx] = gImage->pixel(x, y);
				}
			}
		}
		++gCount;
	}
}
```

优化后的transform

```C++
	void transformPosition(int* oX, int* oY, int iX, int iY, double offsetX, double offsetY, double radius)
	{
		double dX = static_cast<double>(iX);
		double dY = static_cast<double>(iY);

		dX += 0.5f;
		dY += 0.5f;
		// 你可以脑补到一个图片向左向上移动他的坐标
		// 此时的图像以左上角为原点
		// 如果不这样做那么他会把整个图片绕着屏幕左上角的点旋转和大风车一样
		dX -= offsetX;
		dY -= offsetY;

		double sine = sin(radius);		// y
		double cosine = cos(radius);		// x
		// 神奇的公式
		double tempX = cosine * dX - sine * dY;
		double tempY = sine * dX + cosine * dY;

		dX = tempX;
		dY = tempY;
		// 将图片位置还原
		dX += offsetX;
		dY += offsetY;
		dX -= 0.5f;
		dY -= 0.5f;
		*oX = round(dX);
		*oY = round(dY);
	}

```

## 12.2 引入向量和矩阵

其实就是打包数据方便计算出错  矩阵也是一样  至于矩阵的四个值是怎么来的需要在纸上计算作者似乎说在12.8(插眼)会有推导说明

引入向量Vector

```C++
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
class Vector
{
public:
	Vector(); // 空向量
	Vector(int x, int y); // 带有值的初始化向量 int
	Vector(double x, double y);
	~Vector();

	void operator+=(const Vector&); // 向量加法
	void operator-=(const Vector&);	// 向量减法
	void operator=(const Vector&);	// 向量复制

	//向量 
	double x;
	double y;
};
Vector::Vector() :x(0), y(0) {}
Vector::Vector(int ix, int iy)
{
	x = static_cast<double>(ix);
	y = static_cast<double>(iy);
};
Vector::Vector(double ix, double iy) :x(ix), y(iy) {}
Vector::~Vector() {}
void Vector::operator+=(const Vector& thatVector)
{
	x += thatVector.x;
	y += thatVector.y;
}
void Vector::operator-=(const Vector& thatVector)
{
	x -= thatVector.x;
	y -= thatVector.y;
}
void Vector::operator=(const Vector& thatVector)
{
	x = thatVector.x;
	y = thatVector.y;
}

/*--------------------------------------------*/ // MainLoop
namespace GameLib
{
	int round(double a)
	{
		a += (a > 0.0) ? 0.5 : -0.5f;
		return static_cast<int>(a);
	}
	void transformPosition(int* oX, int* oY, int iX, int iY, const Vector& offset, double radius)
	{
		Vector vector(iX, iY);
		Vector tempVector(0.5, 0.5);
		//如果以下面的方式来写那么最后还原位置时会多出两步计算
		//vector += tempVector;
		//vector -= offset;

		tempVector -= offset;
		vector += tempVector;

		double sine = sin(radius);			// y
		double cosine = cos(radius);		// x
		// 神奇的公式
		Vector transAfter;
		transAfter.x = cosine * vector.x - sine * vector.y;
		transAfter.y = sine * vector.x + cosine * vector.y;

		transAfter -= tempVector;			// 还原的位置

		*oX = round(transAfter.x);
		*oY = round(transAfter.y);
	}

	bool init = true;
	unsigned* vram;
	int gCount = 0;
	Image* gImage;
	void Framework::update() {
		if (init) {
			gImage = new Image("E:/environment/GameLib/src/03_2DGraphics2/displayImage/bar.dds");
			init = false;
		}
		unsigned* vram = videoMemory();
		int ww = width(); //window width
		int wh = height(); //window height
		//全黑
		for (int i = 0; i < ww * wh; ++i) {
			vram[i] = 0;
		}
		int iw = gImage->iWidth(); //image width
		int ih = gImage->iHeight(); //image height
		double offsetX = static_cast<double>(iw) / 2.0;
		double offsetY = static_cast<double>(ih) / 2.0;

		double rotation = static_cast<double>(gCount);
		for (int y = 0; y < ih; ++y) {
			for (int x = 0; x < iw; ++x) {
				//计算轮换目的地
				int rx, ry;
				Vector offset(offsetX, offsetY);
				transformPosition(&rx, &ry, x, y, offset, rotation);
				//如果在范围内则粘贴
				if (rx >= 0 && rx < ww && ry >= 0 && ry < wh) {
					vram[ry * ww + rx] = gImage->pixel(x, y);
				}
			}
		}
		++gCount;
	}
}
```

```C++
	/*param1 需要输出的向量  param2输入的向量 param3 中心坐标 param4 2*2矩阵 oVector是输出的旋转后的坐标*/
	void transformPosition(Vector* oVector, Vector& iVector, const Vector& offset, Matrix22 matrix)
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
```

## 12.3 利用定点来实现

```C++
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
class Vector
{
public:
	Vector(); // 空向量
	Vector(int x, int y); // 带有值的初始化向量 int
	Vector(double x, double y);
	~Vector();

	void operator+=(const Vector&); // 向量加法
	void operator-=(const Vector&);	// 向量减法
	void operator=(const Vector&);	// 向量复制

	//向量 
	double x;
	double y;
};
Vector::Vector() :x(0), y(0) {}
Vector::Vector(int ix, int iy)
{
	x = static_cast<double>(ix);
	y = static_cast<double>(iy);
};
Vector::Vector(double ix, double iy) :x(ix), y(iy) {}
Vector::~Vector() {}
void Vector::operator+=(const Vector& thatVector)
{
	x += thatVector.x;
	y += thatVector.y;
}
void Vector::operator-=(const Vector& thatVector)
{
	x -= thatVector.x;
	y -= thatVector.y;
}
void Vector::operator=(const Vector& thatVector)
{
	x = thatVector.x;
	y = thatVector.y;
}
/*--------------------------------------------*/ // Matrix
class Matrix22  // 2*2的矩阵
{
public:
	Matrix22(double im00, double im01, double im10, double im11);
	~Matrix22();
	void multiply(Vector* out, const Vector& in)const;

	double m00, m01, m10, m11;
private:

};

Matrix22::Matrix22(double im00, double im01, double im10, double im11) :
	m00(im00), m01(im01), m10(im10), m11(im11)
{
}

Matrix22::~Matrix22()
{
}
void Matrix22::multiply(Vector* out, const Vector& in)const
{
	double tempx = in.x;
	double tempy = in.y;

	out->x = tempx * m00 + tempy * m01;
	out->y = tempx * m10 + tempy * m11;
}
/*--------------------------------------------*/ // MainLoop
namespace GameLib
{
	int round(double a)
	{
		a += (a > 0.0) ? 0.5 : -0.5f;
		return static_cast<int>(a);
	}
	void transformPosition(Vector* oVector, Vector& iVector, const Vector& offset, Matrix22 matrix)
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

	bool init = true;
	unsigned* vram;
	int gCount = 0;
	Vector Oa(0, 0), Ob(100.0, 0.0), Oc(0.0, 100.0); 	// 首先是需要三个角点  分别是(0,0) (4,0) (0,4)
	Vector Oo(50.0, 50.0);								// 原点坐标
	void Framework::update() {
		if (init) {
			init = false;
			vram = videoMemory();
		}
		Matrix22 matrix22(cos(gCount), -sin(gCount), sin(gCount), cos(gCount));
		// 对角点进行旋转
		Vector tmp(0, 0);
		transformPosition(&tmp, Oa, Oo, matrix22);
		int x = round(tmp.x);
		int y = round(tmp.y);
		if (y >= 0 && x >= 0)
		{
			vram[y * width() + x] = 0xffffffff;
		}

		transformPosition(&tmp, Ob, Oo, matrix22);
		x = round(tmp.x);
		y = round(tmp.y);
		if (y >= 0 && x >= 0)
		{
			vram[y * width() + x] = 0xffffff00;
		}

		transformPosition(&tmp, Oc, Oo, matrix22);
		x = round(tmp.x);
		y = round(tmp.y);
		if (y >= 0 && x >= 0)
		{
			vram[y * width() + x] = 0xffff00ff;
		}



		//int bx = round(Ob.x);
		//int by = round(Ob.y);

		//int cx = round(Oc.x);
		//int cy = round(Oc.y);

		vram[50 * width() + 50] = 0xffffff00;
		//vram[by * width() + bx] = 0xffffffff;
		//vram[cy * width() + cx] = 0xffffffff;


		++gCount;
	}
}
```
