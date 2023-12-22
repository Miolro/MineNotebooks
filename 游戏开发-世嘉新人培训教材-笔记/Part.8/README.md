# 第八章 2D平面内的碰撞处理

碰撞检测(conllision detection) 是否发生碰撞
碰撞相应(conllision response) 碰撞的反馈和行为

相交检测(intersection test) 检测四边形或者圆形之间是否发生了重叠

[8.1碰撞检测](#81-碰撞检测-目录)

[8.2碰撞相应](#82-碰撞相应-目录)

## 8.1 碰撞检测 [目录](#第八章-2d平面内的碰撞处理)

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

### 8.2 碰撞相应 [目录](#第八章-2d平面内的碰撞处理)

- 物块移动  碰撞响应
  
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
