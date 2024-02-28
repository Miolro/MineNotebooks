# 第十三章 显卡的力量

## 13.1 关于使用的类库

笔者指明从这里开始没有VideoMemory()表面无法对像素点逐个计算,
还有就是每次更新到下一帧都会清空画面变成黑色

## 13.2 使用显卡绘制三角形

### 13.2.1 绘制白色三角形

```C++
#include "GameLib/Framework.h"

namespace GameLib
{
	void Framework::update()
	{
		double a[2] = { 100.00,100.00 };
		double b[2] = { 200.00,120.00 };
		double c[2] = { 120.00,200.00 };
		// drawTriangle2D(a, b, c, 0, 0, 0, 0xffff0000, 0xffffffff, 0xff0000ff);
	}
}
```

### 13.3 将图像贴到三角形中

在3D学中这种图像称为`纹理(texture)`,纹理标识3DCG中贴到三角形的图像中,将`贴到三角形的图像`称为纹理，过程称为`纹理贴图`

### 13.3.1 创建纹理

首先创建显卡可用的纹理

### 13.3.2 使用纹理

1. 告诉显卡使用什么纹理
2. 为顶点设置纹理坐标并绘制三角形

``` C++
	setTexture(texture);
```

``` C++
#include "GameLib/Framework.h"
#include "Image.h"
namespace GameLib
{
	bool ginit = false;
	Texture* texture;
	Image* image;
	void Framework::update()
	{
		if (!ginit)
		{
			image = new Image("background.dds");
			createTexture(&texture, image->iWidth(), image->iHeight(), image->data(), image->iWidth(), image->iHeight());
			SAFE_DELETE(image);
			ginit = true;
		}
		setTexture(texture);
		double a[2] = { 100.00,100.00 };
		double b[2] = { 200.00,120.00 };
		double c[2] = { 120.00,200.00 };

		double ta[2] = { 0.0,0.0 };
		double tb[2] = { 1.0,0.0 };
		double tc[2] = { 0.0,1.0 };

		drawTriangle2D(a, b, c, ta, tb, tc);
	}
}
```

### 13.3.4 同时使用纹理和顶点颜色

```C++
drawTriangle2D(a, b, c, ta, tb, tc,0xffffff00,0xffff00ff,0xff00ffff);
```

## 13.4 混合模式

## 13.5 旋转、缩放和移动

老样子  我们使用矩阵计算出四个点所在的位置
然后对图像(纹理进行补间)只不过补间操作交给了显卡

```C++
#include "GameLib/Framework.h"
#include "Image.h"
#include "Matrix23.h"
#include "GameLib/Math.h"
#include "Vector2.h"
namespace GameLib
{
	bool ginit = false;
	Texture* texture;
	Image* image;
	int gCount = 0;
	void Framework::update()
	{
		if (!ginit)
		{
			image = new Image("background.dds");
			createTexture(&texture, image->iWidth(), image->iHeight(), image->data(), image->iWidth(), image->iHeight());
			//SAFE_DELETE(image);
			ginit = true;
		}
		setTexture(texture);
		double sine = sin(gCount);
		double cosine = cos(gCount);
		Matrix23 matrix23(cosine, -sine, 0, sine, cosine, 0);
		Vector2 imageOffset(image->iWidth()/2, image->iHeight()/2);
		
		Vector2 iP0(50.0, 50.0);
		Vector2 iP1 = iP0, iP2 = iP0, iP3 = iP0;

		Vector2 imageVW(image->iWidth() + 0.0, 0.0);
		Vector2 imageVH(0.0, image->iWidth() + 0.0);
		Vector2 imageVWH(image->iWidth() + 0.0, image->iHeight() + 0.0);

		iP1 += imageVW;
		iP2 += imageVH;
		iP3 += imageVWH;
		imageOffset += iP0;
		matrix23.transfromRoll(&iP0, iP0, imageOffset);
		matrix23.transfromRoll(&iP1, iP1, imageOffset);
		matrix23.transfromRoll(&iP2, iP2, imageOffset);
		matrix23.transfromRoll(&iP3, iP3, imageOffset);

		double p0[2] = { iP0.x,iP0.y };
		double p1[2] = { iP1.x,iP1.y };
		double p2[2] = { iP2.x,iP2.y };
		double p3[2] = { iP3.x,iP3.y };

		double resizep0[2] = { 0.0,0.0 };
		double resizep1[2] = { 1.0,0.0 };
		double resizep2[2] = { 0.0,1.0 };
		double resizep3[2] = { 1.0,1.0 };

		drawTriangle2D(p0, p1, p2, resizep0, resizep1, resizep2);
		drawTriangle2D(p3, p1, p2, resizep3, resizep1, resizep2);
		gCount++;
	}
}
```

由于过于复杂 所以进行简化