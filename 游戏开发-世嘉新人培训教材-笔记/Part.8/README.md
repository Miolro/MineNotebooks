# 第八章 2D平面内的碰撞处理

碰撞检测(conllision detection) 是否发生碰撞
碰撞相应(conllision response) 碰撞的反馈和行为

相交检测(intersection test) 检测四边形或者圆形之间是否发生了重叠

[8.1碰撞检测](#81-碰撞检测)

[8.2碰撞响应](#82-碰撞响应)

[8.3多物体碰撞](#83-发生多个碰撞时的问题)

[8.4碰撞响应与操作性](#84-碰撞响应与操作性)

[附加页:单物体碰撞](#附加页单物体碰撞)

## 8.1 碰撞检测

### 8.1.1 正方形的相交检测

如果A与B正方形上下边范围内出现重叠区域表示两者碰撞了

```C++
// 书中代码似乎是A盒子左边的值小于B盒子右边的值表示碰撞
// A盒子右边的值大于B盒子的左边表示碰撞
if((ABox.mLeft<BBox.mRight)&&(ABox.mRight>BBox.mLeft))
{
    // 碰撞
}else{
    // 没碰撞
}

```

### 8.1.2 数据结构

- 存储方式1(存储4边位置)
  
```C++
// 单纯脑补
class Square
{
    public:
        int mL; // left 左边
        int mT; // top  上边
        int mR; // right 右边
        int mB; // bottom 下边
}
```

每次移动需要一次性更新4个值
但是碰撞检测只需要比较相对边的大小

- 存储方式2(存储中心的位置)

```C++
class Square
{
    public:
        int mX; // 中心点X
        int mY; // 中心点Y
        int mHalfSize; // 一半尺寸
}
```

每次移动只需要更新两个值
但是每次碰撞检测时都需要计算出4边的坐标

数据格式会稍微影响处理流程然后影响执行速度

### 8.1.3 用于判断相交的代码

- 碰撞检测

```C++
bool isIntersected(const Object& object)const
{
	// 右边 mx+half
	// 左边 mx-half
	int thisObjL = mX - mHalfSize;
	int thisObjR = mX + mHalfSize;
	int thatObjL = object.mX - object.mHalfSize;
	int thatObjR = object.mX + object.mHalfSize;
	//   →+
	// ↓
	// +
	// 向右向下为正坐标
	// 脑补分析一下
	// 这里表示如果这个对象的左边的的值小于那个对象的右边那么表示横向相交
	// 如果这个对象的右边大于那个对象的左边位置表示横向相交
	// 这里只是横向判断 当横向复合条件时去看纵向的数值
	if ((thisObjL < thatObjR) && (thisObjR > thatObjL))
	{
		//断点走到了这里表示方块的左边或者右边已经侵入
		int thisObjT = mY - mHalfSize;
		int thisObjB = mY + mHalfSize;
		int thatObjT = object.mY - object.mHalfSize;
		int thatObjB = object.mY + object.mHalfSize;
		// 这边开始判断纵向
		// 脑补分析
		// 如果这个对象的顶部坐标小于那个对象的底部坐标那么表示纵向相交
		// 如果这个对象的底部坐标大于那个对象的顶部坐标那表示纵向相交
		if ((thisObjT < thatObjB) && (thisObjB > thatObjT))
		{
			//当两个条件都满足时表示 纵横都相交
			return true;
		}
	}
	return false;
}
    
```

## 8.2 碰撞响应

### 8.2.1 如果移动后发生碰撞则停止移动

- 物块移动  碰撞响应

代码缺陷  如果非移动长度能完美整除的情况会出现没有碰撞发生碰撞响应  可以尝试把moveY或者moveX改为+-7或者其他值

书中说的非常形象 此时你的方块与静态的方块距离为2但是你移动的距离是3  此时执行移动后会触发碰撞响应  但是实际上两个方块并没有发生碰撞 中间还隔着一个像素

```C++
    // 移动控制
char keyList[4] = { 'w','s','a','d' };
int moveX = 0;
int moveY = 0;
for (int i = 0; i < sizeof(keyList); i++)
{
	if (isKeyOn(keyList[i]))
	{
		switch (keyList[i])
		{
		case'w':moveY = -1; break;
		case's':moveY = +1; break;
		case'a':moveX = -1; break;
		case'd':moveX = +1; break;
		}
	}
}
gDynamics->mX += moveX;
gDynamics->mY += moveY;
// 碰撞后抵消前面偏移的加  碰撞后变色
if (gDynamics->isIntersected(*gStatic))
{
	color = 0xffff00ff;
	// +=move -=move = 0 所以偏移被抵消
	gDynamics->mX -= moveX;
	gDynamics->mY -= moveY;
}

```

### 8.2.2 碰撞前停止移动

基本逻辑 发生碰撞 然后后退二分之一,然后再检测再后退四分之一,然后在检测然后八分之一....
直到缩短到合适距离--二分查找法

原本是需要移动7格  但是7格会发生碰撞  此时取二分之一 依然发生碰撞 然后再取四分之一(二分之一的二分之一)然后还是碰撞 最后取八分之一时没有碰撞 求得比率是八分之一 然后用八分之一与本应该移动的7格相乘得带最后移动的数

```C++
// 克隆一个模拟对象 书中示例
Object model(gDynamics->mX, gDynamics->mY, gDynamics->mHalfSize);
// 循环4次判断
int modelX = moveX;
int modelY = moveY;
int a = 1; // 分子
int b = 1; // 分母
int finalA = 0;
int finalB = 0;
for (int i = 0; i < 4; i++)
{
	// 查看模拟对象在移动后是否发生碰撞
	a *= 2;
	b *= 2;
	model.set(gDynamics->mX + modelX, gDynamics->mY + modelY);
	if (model.isIntersected(*gStatic))
	{
		color = 0xffffffff;
		a -= 1;
	}
	else
	{
		// 最后输出的值
		finalA = modelX;
		finalB = modelY;
		break;
	}
	// 应该移动的值 刷新应该使用的比例
	modelX = moveX * a / b;
	modelY = moveY * a / b;
}
gDynamics->mX += finalA;
gDynamics->mY += finalB;
```

函数封装(自行封装用于理解)

```C++
// 模拟碰撞前停止对象移动
bool stopMoveBeforePenetration(const Object& object, const int moveX, const int moveY) {
	// 拷贝一份数据用于模型的尝试移动
	int moveXCopy = moveX;
	int moveYCopy = moveY;
	// 二分法参数
	int numerator = 1;
	int denominator = 1;
	// 循环次数(次数越高精度越高)
	int loopCount = 4; 
	// 拷贝一份this模型来测试移动
	Object model(mX + moveX, mY + moveY, mHalfSize);
	// 如果没有发生碰撞那么直接输出
	if (!model.isIntersected(object))
	{
		mX += moveX;
		mY += moveY;
		return false;
	}
	for (int i = 0; i < loopCount; i++)
	{
		model.set(mX + moveXCopy, mY + moveYCopy);
		numerator *= 2;
		denominator *= 2;
		if (model.isIntersected(object))
		{
			// 如果碰撞那么数值减半
			// 分母翻倍  分子*2-1 所以分子永远是1分母会变为2,4,8,16
			numerator -= 1;
		}
		else
		{
			// 没发生碰撞停止循环并输出比例
			numerator += 1; // 意义不明的加法

			mX += moveXCopy;
			mY += moveYCopy;
			return true;
		}
		// 分母改变后反馈到移动距离再重新判断
		moveXCopy = moveX * numerator / denominator;
		moveYCopy = moveY * numerator / denominator;
	}
}
```

### 8.2.3 穿透后如何恢复

[8.2.1](#821-如果移动后发生碰撞则停止移动)
[8.2.2](#822-碰撞前停止移动)
这两章都是讲的如何避免穿透,换一个思路如果碰撞后逆向移动回到未穿透的时候

- 碰撞的方向\
	书中给出一个图问你这两个正方形嵌入了多少深,图中很容易看出嵌入多少距离,但是还是给出来不知道的答案\
	后面也给出来解释<span style='color:yellow'>如果动态方块是左边撞过来的那么距离就是那么点.但是如果方块是右边来的`我也觉得不可思议,但是有很合理`,那个方块一次性跨越了比静态方块的宽要长的距离正好卡在了和左边来时候都相同位置,那嵌入的深度是多少呢,如果他的移动速度再快(单次运动的步长)那它直接就是闪现穿越了静态方块</span>

在移动速度为+-1px的情况下运行(横向判断的模型)

```C++
gDynamics->mX += moveX;
gDynamics->mY += moveY;
if (gDynamics->solvePenetration(*gStatic))
{
	color = 0xffffffff;
	// 右边比较左边  // 重点注意括号 减法带入括号要变号
	int penetrationFromLeft = (gDynamics->mX + gDynamics->mHalfSize) - (gStatic->mX - gStatic->mHalfSize);
	int penetrationFromRight = (gStatic->mX + gStatic->mHalfSize) - (gDynamics->mX - gDynamics->mHalfSize);
	if (penetrationFromLeft < penetrationFromRight)
	{
		gDynamics->mX -= penetrationFromLeft;
	}
	else
	{
		gDynamics->mX += penetrationFromRight;
	}
}
```

左右可以在发生碰撞时停止移动但是在上下时会判断左右的最短的距离向那个方向移动,最后上下移动如果发生碰撞会向斜方向移动

XY轴碰撞后反向移动的代码(函数封装)

```C++
bool solvePenetration(const Object& object) {
	// 计算出box的模型大小
	int thisBoxL = mX - mHalfSize;
	int thisBoxR = mX + mHalfSize;
	int thisBoxT = mY - mHalfSize;
	int thisBoxB = mY + mHalfSize;
	// 计算出相比较的模型大小
	int thatBoxL = object.mX - object.mHalfSize;
	int thatBoxR = object.mX + object.mHalfSize;
	int thatBoxT = object.mY - object.mHalfSize;
	int thatBoxB = object.mY + object.mHalfSize;
	// 判断是否碰撞
	bool hitX = (thisBoxR > thatBoxL) && (thisBoxL < thatBoxR) ? true : false;
	bool hitY = (thisBoxB > thatBoxT) && (thisBoxT < thatBoxB) ? true : false;
	if (hitX && hitY)
	{
		// 计算嵌入距离
		
		// 修正偏移的方向
		int reverseX = 0;
		int reverseY = 0;
		// 偏移距离
		int shiftSizeX = 0;
		int shiftSizeY = 0;
		int penetrationXR = thisBoxR - thatBoxL;  // 右边进入时
		int penetrationXL = thatBoxR - thisBoxL;  // 左进入时
		//GameLib::cout << penetrationXR << ',' << penetrationXL << GameLib::endl;
		if (penetrationXR < penetrationXL)
		{
			reverseX = -1;
			shiftSizeX += penetrationXR;
		}
		else
		{
			reverseX = +1;
			shiftSizeX += penetrationXL;
		}
		// 计算嵌入距离
		int penetrationYT = thisBoxB - thatBoxT;  // 上边进入时
		int penetrationYB = thatBoxB - thisBoxT;  // 下进入时
		//GameLib::cout << penetrationXR << ',' << penetrationXL << GameLib::endl;
		if (penetrationYT < penetrationYB)
		{
			reverseY = -1;
			shiftSizeY += penetrationYT;
		}
		else
		{
			reverseY = +1;
			shiftSizeY += penetrationYB;
		}
		// 判断是哪个轴进行碰撞
		// 碰撞数据分析
		// 1,9 // 比较小的轴就是碰撞的那个轴
		// 带上符号表示碰撞时需要移动的方向-1为向左移动
		if (shiftSizeX < shiftSizeY)
		{
			mX += shiftSizeX * reverseX;
		}
		else
		{
			mY += shiftSizeY * reverseY;
		}
		GameLib::cout << shiftSizeX * reverseX << ',' << shiftSizeY * reverseY << GameLib::endl;
		return true;
	}
	return false;
}

```

依然还是高速移动下的问题如果速度是15帧移动会变得诡异

### 8.2.4 哪种方法更好

书中说了没有更好的方法,所有的方法只有适用和适合,实际场景不同用的方法也会不同

## 8.3 发生多个碰撞时的问题

### 8.3.1 如果移动后会发生碰撞则停止移动

书中只有一句话:只要有一个物体发生碰撞就停止移动

### 8.3.2

如果多次迭代"[移动后会发生碰撞则停止移动](#821-如果移动后发生碰撞则停止移动)"就需要对所有物体进行检测使物品移动到可以移动的极限位置

如果采用计算碰撞时刻都做法,就需要求出所有对象的碰撞时刻,把最小值作为结束时刻

### 8.3.3 发生嵌入后再调整


### 8.3.4 如何选择

???

## 8.4 碰撞响应与操作性

### 8.4.1 改变外观和实体尺寸

```C++
//hitbox 10
gDynamics = Object(32, 32, 10);
```

### 8.4.2 碰撞后沿着墙壁滑动

调用代码

```C++
gDynamics.fixMove(gStatic[i][j], moveX, moveY);
```

实现内容  检测半边碰撞

```C++
// 移动修正 8.4.2
		void fixMove(const Object& object, int moveX, int moveY) {

			Object model1(mX, mY, mHalfSize);
			Object model2(mX, mY, mHalfSize);
			if (moveX)
			{
				// 如果x轴移动时发生碰撞就去设置两个模拟对象,然后判断上下是否可以移动
				model1.mY += mHalfSize;  // 下半部分
				model2.mY -= mHalfSize;  // 上半部分
			}
			else
			{
				model1.mX += mHalfSize;  // 右半部分
				model2.mX -= mHalfSize;  // 左半部分
			}
			bool model1Hit = false;
			bool model2Hit = false;
			if (model1.isIntersected(object))
			{
				model1Hit = true;
			}
			if (model2.isIntersected(object))
			{
				model2Hit = true;
			}
			//  书中默认以一个方向移动
			if (moveX) {
				if (model1Hit && !model2Hit) { //当它向上移动时不会撞到。向上移动。
					mY -= 1;
				}
				else if (model2Hit && !model1Hit) { //如果它向下移动，它不会碰撞。往下移
					mY += 1;
				}
			}
			else {
				if (model1Hit && !model2Hit) { //向左移动时不会命中。将其向左移动。
					mX -= 1;
				}
				else if (model2Hit && !model1Hit) { //向右移动时不会命中。向右移动
					mX += 1;
				}
			}
		}
```

## 附加页:单物体碰撞

代码肯定是没有书里的精简的主要是用于理解

```C++
#include "GameLib/Framework.h"
#include "core/MainFrame.h"
namespace GameLib {

	class Object
	{
	public:
		Object() {};
		Object(int x, int y, int halfSize)
		{
			mX = x;
			mY = y;
			mHalfSize = halfSize;
		};
		// 碰撞检测 传入相对的一个对象
		bool isIntersected(const Object& object)
		{
			// 右边 mx+half
			// 左边 mx-half
			int thisObjL = mX - mHalfSize;
			int thisObjR = mX + mHalfSize;

			int thatObjL = object.mX - object.mHalfSize;
			int thatObjR = object.mX + object.mHalfSize;
			//   →+
			// ↓
			// +
			// 向右向下为正坐标
			// 脑补分析一下
			// 这里表示如果这个对象的左边的的值小于那个对象的右边那么表示横向相交
			// 如果这个对象的右边大于那个对象的左边位置表示横向相交
			// 这里只是横向判断 当横向复合条件时去看纵向的数值
			if ((thisObjL < thatObjR) && (thisObjR > thatObjL))
			{
				//断点走到了这里表示方块的左边或者右边已经侵入
				int thisObjT = mY - mHalfSize;
				int thisObjB = mY + mHalfSize;

				int thatObjT = object.mY - object.mHalfSize;
				int thatObjB = object.mY + object.mHalfSize;
				// 这边开始判断纵向
				// 脑补分析
				// 如果这个对象的顶部坐标小于那个对象的底部坐标那么表示纵向相交
				// 如果这个对象的底部坐标大于那个对象的顶部坐标那表示纵向相交
				if ((thisObjT < thatObjB) && (thisObjB > thatObjT))
				{
					//当两个条件都满足时表示 纵横都相交
					return true;
				}
			}
			return false;
		}
		// 模拟碰撞前停止对象移动
		bool stopMoveBeforePenetration(const Object& object, int moveX, int moveY) {
			// 拷贝一份数据用于模型的尝试移动
			int moveXCopy = moveX;
			int moveYCopy = moveY;
			// 二分法参数
			int numerator = 1;
			int denominator = 1;
			// 循环次数(次数越高精度越高)
			int loopCount = 4;
			// 拷贝一份this模型来测试移动
			Object model(mX + moveX, mY + moveY, mHalfSize);
			// 如果没有发生碰撞那么直接输出
			if (!model.isIntersected(object))
			{
				mX += moveX;
				mY += moveY;

				return false;
			}
			for (int i = 0; i < loopCount; i++)
			{
				model.set(mX + moveXCopy, mY + moveYCopy, mHalfSize);
				numerator *= 2;
				denominator *= 2;
				if (model.isIntersected(object))
				{
					// 如果碰撞那么数值减半
					// 分母翻倍  分子*2-1 所以分子永远是1分母会变为2,4,8,16
					numerator -= 1;
				}
				else
				{
					// 没发生碰撞停止循环并输出比例
					numerator += 1; // 意义不明的加法

					mX += moveXCopy;
					mY += moveYCopy;
					return true;
				}
				// 分母改变后反馈到移动距离再重新判断
				moveXCopy = moveX * numerator / denominator;
				moveYCopy = moveY * numerator / denominator;
			}
		}
		// 碰撞嵌入后还原
		bool solvePenetration(const Object& object) {
			// 计算出box的模型大小
			int thisBoxL = mX - mHalfSize;
			int thisBoxR = mX + mHalfSize;
			int thisBoxT = mY - mHalfSize;
			int thisBoxB = mY + mHalfSize;
			// 计算出相比较的模型大小
			int thatBoxL = object.mX - object.mHalfSize;
			int thatBoxR = object.mX + object.mHalfSize;
			int thatBoxT = object.mY - object.mHalfSize;
			int thatBoxB = object.mY + object.mHalfSize;
			// 判断是否碰撞
			bool hitX = (thisBoxR > thatBoxL) && (thisBoxL < thatBoxR) ? true : false;
			bool hitY = (thisBoxB > thatBoxT) && (thisBoxT < thatBoxB) ? true : false;

			if (hitX && hitY)
			{
				// 计算嵌入距离

				// 修正偏移的方向
				int reverseX = 0;
				int reverseY = 0;
				// 偏移距离
				int shiftSizeX = 0;
				int shiftSizeY = 0;

				int penetrationXR = thisBoxR - thatBoxL;  // 右边进入时
				int penetrationXL = thatBoxR - thisBoxL;  // 左进入时
				//GameLib::cout << penetrationXR << ',' << penetrationXL << GameLib::endl;
				if (penetrationXR < penetrationXL)
				{
					reverseX = -1;
					shiftSizeX += penetrationXR;
				}
				else
				{
					reverseX = +1;
					shiftSizeX += penetrationXL;
				}

				// 计算嵌入距离
				int penetrationYT = thisBoxB - thatBoxT;  // 上边进入时
				int penetrationYB = thatBoxB - thisBoxT;  // 下进入时
				//GameLib::cout << penetrationXR << ',' << penetrationXL << GameLib::endl;

				if (penetrationYT < penetrationYB)
				{
					reverseY = -1;
					shiftSizeY += penetrationYT;
				}
				else
				{
					reverseY = +1;
					shiftSizeY += penetrationYB;
				}
				// 判断是哪个轴进行碰撞
				// 碰撞数据分析
				// 1,9 // 比较小的轴就是碰撞的那个轴
				// 带上符号表示碰撞时需要移动的方向-1为向左移动
				if (shiftSizeX < shiftSizeY)
				{
					mX += shiftSizeX * reverseX;
				}
				else
				{
					mY += shiftSizeY * reverseY;
				}
				GameLib::cout << shiftSizeX * reverseX << ',' << shiftSizeY * reverseY << GameLib::endl;
				return true;
			}

			return false;
		}
		void set(int x, int y, int halfSize)
		{
			mX = x;
			mY = y;
			mHalfSize = halfSize;
		}
		int mX;
		int mY;
		int mHalfSize;
	};

	bool gInit = true;
	Object gDynamics;
	Object gStatic;
	unsigned* vram;
	int vramWidth;
	int vramHeight;
	int moveSpeed = 7;
	void Framework::update() {
		if (gInit)
		{
			gInit = false;
			setFrameRate(60);
			gDynamics = Object(32, 32, 16);
			gStatic = Object(128, 128, 16);
			vram = videoMemory();
			vramWidth = width();
			vramHeight = height();
		}

		unsigned color = 0xffff0000;// 未碰撞时的颜色

		// 移动控制
		char keyList[4] = { 'w','s','a','d' };
		int moveX = 0;
		int moveY = 0;
		// 方向和速度
		for (int i = 0; i < sizeof(keyList); i++)
		{
			if (isKeyOn(keyList[i]))
			{
				switch (keyList[i])
				{
				case'w':moveY = -moveSpeed; break;
				case's':moveY = +moveSpeed; break;
				case'a':moveX = -moveSpeed; break;
				case'd':moveX = +moveSpeed; break;
				}
			}
		}

		//碰撞检测
		if (gDynamics.stopMoveBeforePenetration(gStatic, moveX, moveY))
		{
			color = 0xffffffff;

		}

		// 清空屏幕
		for (int i = 0; i < vramHeight * vramWidth; i++)
		{
			vram[i] = 0x00000000;
		}

		// 绘制静态对象
		int fullSize = gStatic.mHalfSize * 2;
		int originX = gStatic.mX - gStatic.mHalfSize;
		int originY = gStatic.mY - gStatic.mHalfSize;
		for (int i = originY; i < originY + fullSize; i++)
		{
			for (int j = originX; j < originX + fullSize; j++)
			{
				vram[i * vramWidth + j] = 0xff00ffff;
			}
		}

		// 绘制动态对象
		int dyFullSize = gDynamics.mHalfSize * 2;
		int dyOriginX = gDynamics.mX - gDynamics.mHalfSize;
		int dyOriginY = gDynamics.mY - gDynamics.mHalfSize;
		for (int i = dyOriginY; i < dyOriginY + dyFullSize; i++)
		{
			for (int j = dyOriginX; j < dyOriginX + dyFullSize; j++)
			{
				vram[i * vramWidth + j] = color;
			}
		}
	}
}

```

## 附页页:多物体碰撞

代码肯定是没有书里的精简的主要是用于理解

```C++
#include "GameLib/Framework.h"
#include "core/MainFrame.h"
namespace GameLib {

	class Object
	{
	public:
		Object() {};
		Object(int x, int y, int halfSize)
		{
			mX = x;
			mY = y;
			mHalfSize = halfSize;
		};
		// 碰撞检测 传入相对的一个对象
		bool isIntersected(const Object& object)
		{
			// 右边 mx+half
			// 左边 mx-half
			int thisObjL = mX - mHalfSize;
			int thisObjR = mX + mHalfSize;

			int thatObjL = object.mX - object.mHalfSize;
			int thatObjR = object.mX + object.mHalfSize;
			//   →+
			// ↓
			// +
			// 向右向下为正坐标
			// 脑补分析一下
			// 这里表示如果这个对象的左边的的值小于那个对象的右边那么表示横向相交
			// 如果这个对象的右边大于那个对象的左边位置表示横向相交
			// 这里只是横向判断 当横向复合条件时去看纵向的数值
			if ((thisObjL < thatObjR) && (thisObjR > thatObjL))
			{
				//断点走到了这里表示方块的左边或者右边已经侵入
				int thisObjT = mY - mHalfSize;
				int thisObjB = mY + mHalfSize;

				int thatObjT = object.mY - object.mHalfSize;
				int thatObjB = object.mY + object.mHalfSize;
				// 这边开始判断纵向
				// 脑补分析
				// 如果这个对象的顶部坐标小于那个对象的底部坐标那么表示纵向相交
				// 如果这个对象的底部坐标大于那个对象的顶部坐标那表示纵向相交
				if ((thisObjT < thatObjB) && (thisObjB > thatObjT))
				{
					//当两个条件都满足时表示 纵横都相交
					return true;
				}
			}
			return false;
		}
		// 移动修正 8.4.2
		void fixMove(const Object& object, int moveX, int moveY) {

			Object model1(mX, mY, mHalfSize);
			Object model2(mX, mY, mHalfSize);
			if (moveX)
			{
				// 如果x轴移动时发生碰撞就去设置两个模拟对象,然后判断上下是否可以移动
				model1.mY += mHalfSize;  // 下半部分
				model2.mY -= mHalfSize;  // 上半部分
			}
			else
			{
				model1.mX += mHalfSize;  // 右半部分
				model2.mX -= mHalfSize;  // 左半部分
			}
			bool model1Hit = false;
			bool model2Hit = false;
			if (model1.isIntersected(object))
			{
				model1Hit = true;
			}
			if (model2.isIntersected(object))
			{
				model2Hit = true;
			}
			//  书中默认以一个方向移动
			if (moveX) {
				if (model1Hit && !model2Hit) { //当它向上移动时不会撞到。向上移动。
					mY -= 1;
				}
				else if (model2Hit && !model1Hit) { //如果它向下移动，它不会碰撞。往下移
					mY += 1;
				}
			}
			else {
				if (model1Hit && !model2Hit) { //向左移动时不会命中。将其向左移动。
					mX -= 1;
				}
				else if (model2Hit && !model1Hit) { //向右移动时不会命中。向右移动
					mX += 1;
				}
			}
		}
		// 模拟碰撞前停止对象移动
		bool stopMoveBeforePenetration(const Object& object, int moveX, int moveY) {
			// 拷贝一份数据用于模型的尝试移动
			int moveXCopy = moveX;
			int moveYCopy = moveY;
			// 二分法参数
			int numerator = 1;
			int denominator = 1;
			// 循环次数(次数越高精度越高)
			int loopCount = 4;
			// 拷贝一份this模型来测试移动
			Object model(mX + moveX, mY + moveY, mHalfSize);
			for (int i = 0; i < loopCount; i++)
			{
				model.set(mX + moveXCopy, mY + moveYCopy, mHalfSize);
				numerator *= 2;
				denominator *= 2;
				if (model.isIntersected(object))
				{
					// 如果碰撞那么数值减半
					// 分母翻倍  分子*2-1 所以分子永远是1分母会变为2,4,8,16
					numerator -= 1;
				}
				else
				{
					// 没发生碰撞停止循环并输出比例
					numerator += 1; // 意义不明的加法

					mX += moveXCopy;
					mY += moveYCopy;
					return true;
				}
				// 分母改变后反馈到移动距离再重新判断
				moveXCopy = moveX * numerator / denominator;
				moveYCopy = moveY * numerator / denominator;
			}
			return false;
		}
		// 碰撞嵌入后还原
		bool solvePenetration(const Object& object) {
			// 计算出box的模型大小
			int thisBoxL = mX - mHalfSize;
			int thisBoxR = mX + mHalfSize;
			int thisBoxT = mY - mHalfSize;
			int thisBoxB = mY + mHalfSize;
			// 计算出相比较的模型大小
			int thatBoxL = object.mX - object.mHalfSize;
			int thatBoxR = object.mX + object.mHalfSize;
			int thatBoxT = object.mY - object.mHalfSize;
			int thatBoxB = object.mY + object.mHalfSize;
			// 判断是否碰撞
			bool hitX = (thisBoxR > thatBoxL) && (thisBoxL < thatBoxR) ? true : false;
			bool hitY = (thisBoxB > thatBoxT) && (thisBoxT < thatBoxB) ? true : false;

			if (hitX && hitY)
			{
				// 计算嵌入距离

				// 修正偏移的方向
				int reverseX = 0;
				int reverseY = 0;
				// 偏移距离
				int shiftSizeX = 0;
				int shiftSizeY = 0;

				int penetrationXR = thisBoxR - thatBoxL;  // 右边进入时
				int penetrationXL = thatBoxR - thisBoxL;  // 左进入时
				//GameLib::cout << penetrationXR << ',' << penetrationXL << GameLib::endl;
				if (penetrationXR < penetrationXL)
				{
					reverseX = -1;
					shiftSizeX += penetrationXR;
				}
				else
				{
					reverseX = +1;
					shiftSizeX += penetrationXL;
				}

				// 计算嵌入距离
				int penetrationYT = thisBoxB - thatBoxT;  // 上边进入时
				int penetrationYB = thatBoxB - thisBoxT;  // 下进入时
				//GameLib::cout << penetrationXR << ',' << penetrationXL << GameLib::endl;

				if (penetrationYT < penetrationYB)
				{
					reverseY = -1;
					shiftSizeY += penetrationYT;
				}
				else
				{
					reverseY = +1;
					shiftSizeY += penetrationYB;
				}
				// 判断是哪个轴进行碰撞
				// 碰撞数据分析
				// 1,9 // 比较小的轴就是碰撞的那个轴
				// 带上符号表示碰撞时需要移动的方向-1为向左移动
				if (shiftSizeX < shiftSizeY)
				{
					mX += shiftSizeX * reverseX;
				}
				else
				{
					mY += shiftSizeY * reverseY;
				}
				GameLib::cout << shiftSizeX * reverseX << ',' << shiftSizeY * reverseY << GameLib::endl;
				return true;
			}

			return false;
		}
		void set(int x, int y, int halfSize)
		{
			mX = x;
			mY = y;
			mHalfSize = halfSize;
		}
		int mX;
		int mY;
		int mHalfSize;
	};
	// hitbox没有碰撞到墙只是边框碰撞到墙上
	// 视觉模型 tModel
	// 碰撞模型 gDynamics
	// 墙体		gStatic
	bool gInit = true;
	Object gDynamics;
	Object gStatic[2][2];
	unsigned* vram;
	int vramWidth;
	int vramHeight;
	int moveSpeed = 7;
	void Framework::update() {
		if (gInit)
		{
			gInit = false;
			setFrameRate(60);
			//hitbox 10
			gDynamics = Object(32, 32, 10);
			for (int i = 0; i < 2; i++)
			{
				for (int j = 0; j < 2; j++)
				{
					gStatic[i][j].set(i * 64 + 64, j * 64 + 16, 16);
				}
			}
			vram = videoMemory();
			vramWidth = width();
			vramHeight = height();
		}

		unsigned color = 0xffff0000;// 未碰撞时的颜色

		// 移动控制
		char keyList[4] = { 'w','s','a','d' };
		int moveX = 0;
		int moveY = 0;
		// 方向和速度
		for (int i = 0; i < sizeof(keyList); i++)
		{
			if (isKeyOn(keyList[i]))
			{
				switch (keyList[i])
				{
				case'w':moveY = -moveSpeed; break;
				case's':moveY = +moveSpeed; break;
				case'a':moveX = -moveSpeed; break;
				case'd':moveX = +moveSpeed; break;
				}
			}
		}
		//碰撞检测
		gDynamics.set(gDynamics.mX + moveX, gDynamics.mY + moveY, gDynamics.mHalfSize);
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				if (gDynamics.isIntersected(gStatic[i][j]))
				{
					color = 0xffffffff;
					// 碰撞后回溯
					gDynamics.fixMove(gStatic[i][j], moveX, moveY);
					gDynamics.set(gDynamics.mX - moveX, gDynamics.mY - moveY, gDynamics.mHalfSize);
					gDynamics.stopMoveBeforePenetration(gStatic[i][j], moveX, moveY);
					// 碰撞后沿着墙壁移动 8.4.2
					
				}
			}
		}
		// 清空屏幕
		for (int i = 0; i < vramHeight * vramWidth; i++)
		{
			vram[i] = 0x00000000;
		}

		// 绘制静态对象 多个墙体绘制
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				int fullSize = gStatic[i][j].mHalfSize * 2;
				int originX = gStatic[i][j].mX - gStatic[i][j].mHalfSize;
				int originY = gStatic[i][j].mY - gStatic[i][j].mHalfSize;
				for (int i = originY; i < originY + fullSize; i++)
				{
					for (int j = originX; j < originX + fullSize; j++)
					{
						vram[i * vramWidth + j] = 0xff00ffff;
					}
				}
			}
		}
		// 缩小碰撞箱 8.4.1
		Object tModel(gDynamics.mX, gDynamics.mY, gDynamics.mHalfSize + 5);
		// 绘制动态对象
		int tMFullSize = tModel.mHalfSize * 2;
		int dyModelX = gDynamics.mX - tModel.mHalfSize;
		int dyModelY = gDynamics.mY - tModel.mHalfSize;
		for (int i = dyModelY; i < dyModelY + tMFullSize; i++)
		{
			for (int j = dyModelX; j < dyModelX + tMFullSize; j++)
			{
				vram[i * vramWidth + j] = color;
			}
		}
		int dyFullSize = gDynamics.mHalfSize * 2;
		int dyOriginX = gDynamics.mX - gDynamics.mHalfSize;
		int dyOriginY = gDynamics.mY - gDynamics.mHalfSize;
		// 绘制动态对象的碰撞体积
		for (int i = dyOriginY; i < dyOriginY + dyFullSize; i++)
		{
			for (int j = dyOriginX; j < dyOriginX + dyFullSize; j++)
			{
				vram[i * vramWidth + j] = 0xffffff00;
			}
		}
	}
}
```
