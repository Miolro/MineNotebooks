# 第八章 2D平面内的碰撞处理

碰撞检测(conllision detection) 是否发生碰撞
碰撞相应(conllision response) 碰撞的反馈和行为

相交检测(intersection test) 检测四边形或者圆形之间是否发生了重叠

[8.1碰撞检测](#81-碰撞检测)

[8.2碰撞响应](#82-碰撞响应)

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

完整代码

```C++
#include "GameLib/Framework.h"
#include "core/MainFrame.h"
namespace GameLib {

	class Object
	{
	public:
		Object(int x, int y, int halfSize)
		{
			mX = x;
			mY = y;
			mHalfSize = halfSize;
		};
		// 碰撞检测 传入相对的一个对象
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
		int mX;
		int mY;
		int mHalfSize;
	};

	bool gInit = true;
	Object* gDynamics;
	Object* gStatic;
	unsigned* vram;
	int vramWidth;
	int vramHeight;
	void Framework::update() {
		if (gInit)
		{
			gInit = false;
			setFrameRate(60);
			gDynamics = new Object(16, 50, 16);
			gStatic = new Object(100, 160, 16);
			vram = Framework::instance().videoMemory();
			vramWidth = Framework::instance().width();
			vramHeight = Framework::instance().height();
		}

		unsigned color = 0xffff0000;// 未碰撞时的颜色

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

		// 碰撞后抵消前面偏移的加
		if (gDynamics->isIntersected(*gStatic))
		{
			color = 0xffff00ff;
			// +=move -=move = 0 所以偏移被抵消
			gDynamics->mX -= moveX;
			gDynamics->mY -= moveY;
		}
		for (int i = 0; i < vramHeight * vramWidth; i++)
		{
			vram[i] = 0x00000000;
		}

		// 绘制静态对象
		for (int i = gStatic->mY - gStatic->mHalfSize; i < gStatic->mY - gStatic->mHalfSize + gStatic->mHalfSize * 2; i++)
		{
			for (int j = gStatic->mX - gStatic->mHalfSize; j < gStatic->mX - gStatic->mHalfSize + gStatic->mHalfSize * 2; j++)
			{
				vram[i * vramWidth + j] = 0xff00ffff;
			}
		}

		// 绘制动态对象
		for (int i = gDynamics->mY - gDynamics->mHalfSize; i < gDynamics->mY - gDynamics->mHalfSize + gDynamics->mHalfSize * 2; i++)
		{
			for (int j = gDynamics->mX - gDynamics->mHalfSize; j < gDynamics->mX - gDynamics->mHalfSize + gDynamics->mHalfSize * 2; j++)
			{
				vram[i * vramWidth + j] = color;
			}
		}
	}
}

```

### 8.2.2 碰撞前停止移动

基本逻辑 发生碰撞 然后后退二分之一,然后再检测再后退四分之一,然后在检测然后八分之一....
直到缩短到合适距离--二分查找法

原本是需要移动7格  但是7格会发生碰撞  此时取二分之一 依然发生碰撞 然后再取四分之一(二分之一的二分之一)然后还是碰撞 最后取八分之一时没有碰撞 求得比率是八分之一 然后用八分之一与本应该移动的7格相乘得带最后移动的数

```C++
		// 克隆一个模拟对象
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

处理后的代码

```C++
#include "GameLib/Framework.h"
#include "core/MainFrame.h"
namespace GameLib {

	class Object
	{
	public:
		Object(int x, int y, int halfSize)
		{
			mX = x;
			mY = y;
			mHalfSize = halfSize;
		};
		// 碰撞检测 传入相对的一个对象
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
		void set(int x, int y)
		{
			mX = x;
			mY = y;
		}
		int mX;
		int mY;
		int mHalfSize;
	};

	bool gInit = true;
	Object* gDynamics;
	Object* gStatic;
	unsigned* vram;
	int vramWidth;
	int vramHeight;
	void Framework::update() {
		if (gInit)
		{
			gInit = false;
			setFrameRate(60);
			gDynamics = new Object(16, 50, 16);
			gStatic = new Object(100, 160, 16);
			vram = Framework::instance().videoMemory();
			vramWidth = Framework::instance().width();
			vramHeight = Framework::instance().height();
		}

		unsigned color = 0xffff0000;// 未碰撞时的颜色

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
				case'w':moveY = -7; break;
				case's':moveY = +7; break;
				case'a':moveX = -7; break;
				case'd':moveX = +7; break;
				}
			}
		}
		// 克隆一个模拟对象
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


		for (int i = 0; i < vramHeight * vramWidth; i++)
		{
			vram[i] = 0x00000000;
		}

		// 绘制静态对象
		for (int i = gStatic->mY - gStatic->mHalfSize; i < gStatic->mY - gStatic->mHalfSize + gStatic->mHalfSize * 2; i++)
		{
			for (int j = gStatic->mX - gStatic->mHalfSize; j < gStatic->mX - gStatic->mHalfSize + gStatic->mHalfSize * 2; j++)
			{
				vram[i * vramWidth + j] = 0xff00ffff;
			}
		}

		// 绘制动态对象
		for (int i = gDynamics->mY - gDynamics->mHalfSize; i < gDynamics->mY - gDynamics->mHalfSize + gDynamics->mHalfSize * 2; i++)
		{
			for (int j = gDynamics->mX - gDynamics->mHalfSize; j < gDynamics->mX - gDynamics->mHalfSize + gDynamics->mHalfSize * 2; j++)
			{
				vram[i * vramWidth + j] = color;
			}
		}
	}
}
```
