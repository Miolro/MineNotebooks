# 第 18 章 3D 碰撞处理

## 18.1 长方体的碰撞处理

首先需要定义一个碰撞箱:

1. 数据结构 1
   - 保存数据的边界位置
2. 数据结构 2
   - 保存碰撞中心
   - 碰撞边界离中心的距离

```C++
   int mX;
   int mY;
   int mZ;
   int mHalfSizeX;
   int mHalfSizeY;
   int mHalfSizeZ;
```

使用整型来做碰撞检测

外部传入的位置信息(Double)->转储为内部单位(Int)

```C++
  mX = static_cast<int>(instancePosition.x * UNIT);
```

位置和边界的大小都使用这样的方法转为内部单位后续使用内部单位作为判断

## 检测部分

和 2d 的判断类似需要判断计算后的边界信息

### X 轴:

- 需要保证 this.右边要大于 that.左边
- 需要保证 this.左边要小于 that.右边

### Y 轴:

- 需要保证 this.上边要大于 that.下边
- 需要保证 this.下边要小于 that.上边

### Z 轴:(你面朝的方向为负方向 越远值越小)

- 需要保证 this.前边要大于 that.后边
- 需要保证 this.后边要小于 that.前边

```C++
bool Cuboid::isIntersectRectTest(const Cuboid& b) const
{
    int selfLeft = mX - mHalfSizeX; // 左边
    int selfRigh = mX + mHalfSizeX; // 右边
    int othLeft = b.mX - b.mHalfSizeX; // 左边-
    int othRigh = b.mX + b.mHalfSizeX; // 右边+
    if ((selfRigh > othLeft) && (othRigh > selfLeft))
    {
        int selfForw = mZ - mHalfSizeZ; // 前面
        int selfBack = mZ + mHalfSizeZ; // 后面
        int othForw = b.mZ - b.mHalfSizeZ; // 前面-
        int othBack = b.mZ + b.mHalfSizeZ; // 后面+
        if ((selfForw < othBack) && (othForw < selfBack))
        {
            int selfTop = mY + mHalfSizeY; // 上面
            int selfBott = mY - mHalfSizeY; // 下面
            int othTop = b.mY + b.mHalfSizeY; // 上面
            int othBott = b.mY - b.mHalfSizeY; // 下面
            if ((selfBott < othTop) && (othBott < selfTop))
            {
                return true;
            }
        }
    }
    return false;
}
```

## 碰撞响应

大体原理为测试现在这个方向移动后是不是发生了碰撞,如果没有那么继续移动,如果发生了碰撞那么就去确定那个面发生了碰撞

判断哪个面发生了碰撞可以用退回单个方向或者多个方向的办法来确定

```C++
void Cuboid::restrictMove(Vector3* direction, const Cuboid& oth) const
{
    int dirX = static_cast<int>(direction->x * UNIT); // 单位距离
    int dirY = static_cast<int>(direction->y * UNIT); // 单位距离
    int dirZ = static_cast<int>(direction->z * UNIT); // 单位距离

    // 测试移动
    Cuboid _this = *this;
    bool r = false;
    _this.mX += dirX;// 测试移动
    _this.mZ += dirZ;// 测试移动
    _this.mY += dirY;// 测试移动

    r = _this.isIntersectRectTest(oth);
    if (!r) {
        int a = 1;
        return; // 没有碰撞
    }
    _this.mZ -= dirZ;// 测试移动
    r = _this.isIntersectRectTest(oth);
    if (!r) {
        direction->z = 0.0;
        return; // 没有碰撞
    }

    _this.mZ += dirZ;// 测试移动
    _this.mX -= dirX;
    r = _this.isIntersectRectTest(oth);
    if (!r) {
        direction->x = 0.0;
        return; // 没有碰撞
    }

    _this.mX += dirX;
    _this.mY -= dirY;
    r = _this.isIntersectRectTest(oth);
    if (!r) {
        direction->y = 0.0;
        return; // 没有碰撞
    }

    _this.mX -= dirX;
    r = _this.isIntersectRectTest(oth);
    if (!r) {
        direction->y = direction->x = 0.0;
        return; // 没有碰撞
    }

    _this.mY += dirY;
    _this.mZ -= dirZ;
    r = _this.isIntersectRectTest(oth);
    if (!r) {
        direction->z = direction->x = 0.0;
        return; // 没有碰撞
    }
    _this.mX += dirX;
    _this.mY -= dirY;
    r = _this.isIntersectRectTest(oth);
    if (!r) {
        direction->z = direction->y = 0.0;
        return; // 没有碰撞
    }
}

```

## 18.2 使用浮点数的碰撞检测(球体检测)

## 碰撞检测

大体思路类似长方体的检测方式

现在有两个圆如果`两个圆的半径>两个之间圆心的距离`那么表示它们相交

```C++
bool Sphere::isIntersectCircleTest(const Sphere& oth) const
{
    Vector3 difference;
    difference.setSub(mPosition, oth.mPosition);
    double squareDistance = difference.squareLength();//求出两圆距离
    double rSum = mRadius + oth.mRadius;// 求出两圆半径和
    rSum *= rSum;
    return (squareDistance < rSum);
}
```

## 碰撞响应

当两个圆相撞之后圆与圆之间的圆心做连线可以得到一个向量,这个向量是需要阻止移动的向量

v-阻止移动的向量=最终可以移动的向量

最总问题就变成了如何去求出这个阻止移动的向量大小和方向

向量方向:

- 圆与圆做连线相减得到的向量

- 将向量除以它的模得到它的单位向量(确定方向)
  
向量的大小:

- 单位向量乘以它的连线(圆心和圆心的连线)那么就得到了它的大小

两个相乘得到最终阻止移动的向量

```C++
Vector3 d;
d.setSub(mPosition, a.mPosition); //c0-c1 = d
double dotDV = d.dot(*v); //dot(d, v)
double dLength2 = d.squareLength(); //|d|^2
d *= (dotDV / dLength2); //dot(b,v) / |d|^2
//最后减法
*v -= d;
```