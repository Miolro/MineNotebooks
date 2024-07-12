#include "GameLib/Framework.h"
#include "GameLib/Math.h"
#include "Image.h"
#include "Vector2.h"
#include "Matrix32.h"

namespace GameLib {
	int round(double a)
	{
		a += (a > 0.0) ? 0.5 : -0.5f;
		return static_cast<int>(a);
	}

	bool initFlag = false;
	Image* image = nullptr;
	Vector2 pointO(50.0, 30.0);
	unsigned* vram;
	int ww = 0;
	int gAngle = 0;
	void drawLine(const Vector2& p0, const Vector2& p1)
	{
		Vector2 v01;
		Vector2 b;
		if (p0.x < p1.x)
		{
			v01.setSub(p0, p1);
			b = p0;
		}
		else {
			v01.setSub(p1, p0);
			b = p1;
		}

		for (int x = 0; x < v01.x; x++)
		{
			double t = x / v01.x;
			Vector2 tv;
			Vector2 tv1;
			tv = b;
			tv1 = v01;
			tv1 *= t;
			tv += tv1;
			vram[round(tv.y) * ww + round(tv.x)] = 0xffffffdd;
		}

	}
	void rasterize(
		// p0 向量基准点  向量由这里开始  p1 点1  点2
		const Vector2& p0, const Vector2& p1, const Vector2& p2,
		// v0 向量0点 v1 以零点开始的向量1  v2 以零点开始的向量2
		const Vector2& v0, const Vector2& v1, const Vector2& v2,
		const Image* image) {
		// 三点排序

		Vector2 tp0, tp1, tp2;
		Vector2 tv0, tv1, tv2;

		// 以y排序 使tp0.y<tp1.y<tp2.y
		// 对三个点(p)和向量(v)排序
		if (p0.y < p1.y) // p0<p1
		{
			if (p1.y < p2.y) // p0 < p1 < p2
			{
				tp0 = p0; tp1 = p1; tp2 = p2;
				tv0 = v0; tv1 = v1; tv2 = v2;
			}
			else if (p0.y < p2.y) { // p0 p2 p1
				tp0 = p0; tp1 = p2; tp2 = p1;
				tv0 = v0; tv1 = v2; tv2 = v1;
			}
			else // p2 p0 p1
			{
				tp0 = p2; tp1 = p0; tp2 = p1;
				tv0 = v2; tv1 = v0; tv2 = v1;
			}
		}
		else {// p1<p0
			if (p0.y < p2.y) // p1 < p0 <p2
			{
				tp0 = p1; tp1 = p0; tp2 = p2;
				tv0 = v1; tv1 = v0; tv2 = v2;
			}
			else if (p1.y < p2.y) { // p1 < p2 < p0
				tp0 = p1; tp1 = p2; tp2 = p0;
				tv0 = v1; tv1 = v2; tv2 = v0;
			}
			else // p2 < p1 < p0
			{
				tp0 = p2; tp1 = p1; tp2 = p0;
				tv0 = v2; tv1 = v1; tv2 = v0;
			}
		}

		// 计算与p1同y轴的p3点

		Vector2 v01, v02, v03;

		v01.setSub(tp0, tp1); // p0->p1 
		v02.setSub(tp0, tp2); // p0->p2 

		Vector2 p3;
		p3.y = tp1.y;
		// p0 -> p1 的垂直距离  v02是p0->p2的垂直距离可以 y轴得到占有比率
		double t = (tp1.y - tp0.y) / v02.y; // 
		p3.x = tp0.x + v02.x * t;

		v03.setSub(tp0, p3);

		drawLine(tp1, p3);
		vram[round(p3.y) * ww + round(p3.x)] = 0xff00ffff;

		
		if (tp1.y > tp0.y + 1.0)
		{
			int ybegin = static_cast<int>(tp0.y);
			int yend = static_cast<int>(tp1.y);
			t = 1.0 / v01.y;
			for (int y = ybegin; y < yend; y++)
			{
				// 零点开始的y向量与当前遍历函数的占比  可以得到其他两个向量x的占比 用y的份数求x的值
				double t1 = (y - tp0.y) * t;
				double x1 = tp0.x + t1 * v01.x;
				double x2 = tp0.x + t1 * v03.x;

				int xbegin = x1 > x2 ? static_cast<int>(x2) : static_cast<int>(x1);
				int xend = x1 < x2 ? static_cast<int>(x2) : static_cast<int>(x1);
				for (int x = xbegin; x < xend; x++)
				{

					double xf = x;
					// 从x，y中找到ix，iy
					Vector2 ip;

					vram[y * ww + x] = 0xffff0000ff;
				}
			}
		}

	}

	void Framework::update()
	{
		if (gAngle > 360)
		{
			gAngle = 1;
		}
		if (!initFlag)
		{
			image = new Image("background.dds");
			ww = width();
			vram = videoMemory();
			initFlag = true;
		}
		for (int i = 0; i < width() * height(); ++i) {
			vram[i] = 0;
		}

		Vector2 pointP1, pointP2, pointP3;
		pointP1.addVector(pointO, Vector2(image->iWidth(), 0));
		pointP2.addVector(pointO, Vector2(0, image->iHeight()));
		pointP3.addVector(pointO, Vector2(image->iWidth(), image->iHeight()));

		vram[round(pointO.y) * ww + round(pointO.x)] = 0xffff0000;
		vram[round(pointP1.y) * ww + round(pointP1.x)] = 0xff00ff00;
		vram[round(pointP2.y) * ww + round(pointP2.x)] = 0xff0000ff;
		vram[round(pointP3.y) * ww + round(pointP3.x)] = 0xffff00ff;
		Vector2 t1, t2, t3;
		Vector2 t4;
		// 移动 不用设置矩阵
		//Matrix32 matrix32;
		//matrix32.transfromMove(&t1, pointO, 2.0, 2.0);
		//matrix32.transfromMove(&t2, pointP1, 2.0, 2.0);
		//matrix32.transfromMove(&t3, pointP2, 2.0, 2.0);

		// 移动  设置矩阵
		//Matrix32 matrix32(1, 0, 10, 0, 1, 20.0);
		//matrix32.transfromMove(&t1, pointO);
		//matrix32.transfromMove(&t2, pointP1);
		//matrix32.transfromMove(&t3, pointP2);

		// 旋转
		double sine = sin(gAngle);
		double cosine = cos(gAngle);
		Matrix32 matrix32(cosine, -sine, 0, sine, cosine, 0);
		Vector2 originP(image->iWidth() / 2, image->iHeight() / 2);
		originP += pointO;

		// 第二个属性是向量长度  第三个属性是左上角距离图像中心位置的坐标
		matrix32.transfromRoll(&t1, pointO, originP);
		matrix32.transfromRoll(&t2, pointP1, originP);
		matrix32.transfromRoll(&t3, pointP2, originP);
		matrix32.transfromRoll(&t4, pointP3, originP);
		// 缩放
		//Matrix32 matrix32(0.5, 0, 0, 0, 0.5, 0);
		//matrix32.transfromScal(&t1, pointO, originP);
		//matrix32.transfromScal(&t2, pointP1, originP);
		//matrix32.transfromScal(&t3, pointP2, originP);
		rasterize(t1, t2, t3, Vector2(0, 0), Vector2(128.0, 0.0), Vector2(0.0, 128.0), nullptr);
		rasterize(t4, t2, t3, Vector2(128.0, 128.0), Vector2(128.0, 0.0), Vector2(0.0, 128.0), nullptr);
		vram[round(t1.y) * ww + round(t1.x)] = 0xffff0000;
		vram[round(t2.y) * ww + round(t2.x)] = 0xff00ff00;
		vram[round(t3.y) * ww + round(t3.x)] = 0xff0000ff;
		drawLine(t1, t2);
		drawLine(t2, t3);
		drawLine(t3, t1);
		drawLine(t4, t2);
		drawLine(t4, t3);
		gAngle++;
	}
}