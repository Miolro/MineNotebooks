# 第十四章  绘制立体物体

## 14.1 关于类库

相比之前的库没有了drawTriangle2D和传递createTexture时只要传入文件名意外没什么改动

### 14.1.1 纹理注册

在`在十四章`之前我们需要手动载入图片文件还要解析DDS文件，但是有一个好消息，我们现在只要提供文件名就可以自动载入并注册图形文件

``` C++
 Framework f = Framework::instance();
 Texture* t;
 f.createTexture(&t,"aho.tga");
```

使用getTextureSizes()获取纹理尺寸，原始素材宽高值，和修改为2的N次放的宽高值

## 14.2 开始制作3D动作游戏《机甲大战》

- 首先一个问题就是之前的视野都是固定的，但是现在随着移动视角视野也是一起变动的
- 在3D空间中,物体越远，看起来越小
- 还有就是遮挡问题，近距离的物体会把远处的物体遮挡
- 还有一个是立体感方面的问题,`2D只不过是把内存中的抽象数据Flag给具象成一个个图片`， 但是在3D中需要考虑环境因素比如阴影光影，需要通过明暗来突出3D空间的立体感
- 还有就是关于3D空间的碰撞使用2D游戏通过四边形之间的相交判断就不足以应对了，我们需要使用浮点来完成计算，当大量的子弹和物品碰撞相交检测还会有性能方面问题，以及地形与物体的碰撞

## 14.3 绘制三角形

依然还是熟悉的绘制三角形，不过这次的参数已经变成了3个，绘制由drawTriangle3D来代替了drawTriangle2D

书中描述了x,y,z表示的意思

x：范围0-640 超出不绘制

y：范围0-480 超出不绘制

z：深度  方向是由内向外的

## 14.4 按位置前后绘制物体

书中例子：两个三角形都设置了z轴为什么远处的（z=1）的三角形覆盖了近处的（z=0）的三角形 ，书上也有解释`执行代码顺序绘制三角形，后绘制的三角形会覆盖之前绘制的三角形`

这里需要使用一些特殊处理，使被遮挡的面不可见，`隐藏面消除`

z-Sort 

    显然从上面的原因解释中就可以知道只要先渲染最远的物体就可以了，这样近处的物体就会遮挡远处的图像（按照z的大小排序依次绘制三角形）

    好处是这块不需要额外的内存开销，曾经广泛使用，现在某些情况也会使用（以前常用，现在有更好的方法可以替代）

    *但是 如果一个三角形中的z轴不在统一z轴上怎么办呢  z-Sort就不适用了

Z缓存

    `如果一个三角形中的z轴不在统一z轴`这以前是很棘手的问题，但是硬件进步问题也解决了。绘制的最小单位是像素，我们可以统计出每个像素被绘制时的z坐标，`给每个像素做Z排序？？？`这样就可以使用三角形为单位，而用更小的像素作为单位来判断前后关系
    
    其中记录各个像素z坐标区域称为z缓存（z-Buffer）,使用这个方法来判断前后关系被叫做`Z缓存法`，过程被叫做z-Test，也被叫做depthBeffer或者 depthTest

### 14.4.1 半透明与Z缓存

enableDeptTest()函数是为了Z缓存无法发挥作用或者明确禁止使用Z缓存时而保留的

- Z缓存无法发挥作用的情况
  
  `有一个半透明三角形，和之前处理一样使用setBlendModel()来开启透明混合，混合后遮挡部分会被忽略`

  ```C++
	double count = 0;
	bool isInit = false;
	void Framework::update()
	{
		if (!isInit)
		{
			isInit = true;
		}
		//double point1[3] = { 500.00,300.00,0.5 };
		//double point2[3] = { 300.00,500.00,0.5 };
		//double point3[3] = { 300.00,300.00,-count };
		//drawTriangle3D(point1, point2, point3);
		//count += 0.1;
		enableDepthTest(true);
		setBlendMode(BLEND_LINEAR);
		//enableDepthWrite(true);  // 为true时 此时的倒三角中的颜色不正常  重叠区域理论上应该发生像素颜色混合  颜色应该与正三角的颜色一致
		double point0[3] = { 200.0,100.0 ,1.0 };
		double point1[3] = { 400.0,100.0 ,1.0 };
		double point2[3] = { 300.0,400.0 ,0.0 };
		unsigned c = 0x80ff0000;
		drawTriangle3D(point0, point1, point2, 0, 0, 0, c, c, c);

		double point3[3] = { 200.0,400.0 ,1.0 };
		double point4[3] = { 400.0,400.0 ,1.0 };
		double point5[3] = { 300.0,100.0 ,0.0 };
		c = 0x8000ff00;
		drawTriangle3D(point3, point4, point5, 0, 0, 0, c, c, c);

	}
  ```
  代码测试后看到会有两个重叠的三角形，正方向的三角形显示看着比较正常，完成了红绿颜色的混合，但是倒三角只是单纯的红色(这显然不对)理论上的结果应该是两个混和区域的三角形的颜色应该是一样的(enableDeptWrite设置为false时两个混合后的颜色一样)
  `因为遵循如果像素被遮挡那么就忽略 所以需要执行Z-Test但是不写入Z缓存`

但是Z-Sort也有一些缺陷  如果透明三角形有上万个那么排序操作会很麻烦

要正确的绘制出透明的混合效果必须把所有的像素都保存下来，然后z值排序混合渲染，但是排序和所有像素取出并排序两个操作成本实在是太高，`折中一下忽略深处的像素来减少计算量，只取考前发两个图形进行运算`

但是只是采用`叠加混合`模式就没什么问题，因为这样的模式不忿先后顺序，但是`线性混合`模式不具备这样的特新，因为比例分配不是一样的

$f(a,b) = f(b,a)$ // 叠加混合  
$f(a,b) = a+t(b-a) =a+tb-ta$  
$f(b,a) = b+t(a-b) =b+ta-tb$

## 14.5 把远处的物体绘制得小一些

### 14.5.1 和距离成反比

简单点题：远近的比例尺，需要一个观察者视角

- 二维中的A(x,y)B(x,y)两点距离  勾股定理
  - $\sqrt{(X_b-X_a)^2+(Y_b-Y_a)^2}$
- 三维中的A(x,y,z)B(x,y,z) 两点距离  勾股定理
  - $\sqrt{(X_b-X_a)^2+(Y_b-Y_a)^2+(Z_b-Z_a)^2}$
- 将物体变小的方法
  - 现在要解决的问题是“被除数应该取什么值”

使用Z轴来当作比例放大的除数,如果离得越近,除数越小，除数越小商越大

但是又衍生出一个问题设定顶点如果Z值超过1或者小于0那么就会使画面消失

以及在计算时除数为零时无意义

如何避免呢：既然是比例尺放大那么我们移动z轴使范围从0-1变为1-2

那Z轴相对*2了那么其他的参数也要相对的\*2以保持比例与范围0-1时的比例一致

```C++
#include "foo.h"
#include "GameLib/Framework.h"
#define Z_MAX_RANGE 2
#define Z_MIN_RANGE 1
namespace GameLib
{
	double count = 0;
	bool isInit = false;
	double position = Z_MIN_RANGE * 1000;
	int dist = 1;
	void Framework::update()
	{
		if (!isInit)
		{
			isInit = true;
		}

		enableDepthTest(true);
		setBlendMode(BLEND_LINEAR);
		enableDepthWrite(true);  // 为true时此时的倒三角中的颜色不正常  重叠区域理论上应该发生像素颜色混合  颜色应该与正三角的颜色一致
		// 深度距离z在0-1的范围中可以显示  如果超出了范围那么就不能显示了eg：-0.1 或是 2
		// 以下处理结束后使z不会因为为0时让图像消失  在某个值时突然覆盖整个画面
		double maxRange = 1000 * Z_MAX_RANGE;  // 使最大的Z为2  保证补间比例没有被扩大
		double minRange = 1000 * Z_MIN_RANGE;  // 使最小值Z为1  保证补间比例没有被扩大

		double resize = position / maxRange;  // 初始化图像  当前位置距离最大位置的比例
		//  经过比例1000的放大之后  position从0-1000来到了1000-2000 相对的maxRange也一样放大比例这样就保证不会因为移动Z轴区间导致图像比例错误

		//  距离与点位的比例
		double point0[3] = { 0.0 / resize,0.0 / resize ,resize };
		double point1[3] = { 300.0 / resize,0.0 / resize ,resize };
		double point2[3] = { 0.0 / resize,300.0 / resize ,resize };
		unsigned c = 0x80555555;
		drawTriangle3D(point0, point1, point2, 0, 0, 0, c, c, c);

		double point3[3] = { 300.0 / resize,300.0 / resize ,resize };
		double point4[3] = { 300.0 / resize,0.0 / resize ,resize };
		double point5[3] = { 0.0 / resize,300.0 / resize ,resize };
		c = 0x80555555;
		drawTriangle3D(point3, point4, point5, 0, 0, 0, c, c, c);
		if ((position += dist) > maxRange)
		{
			dist = -1;
		}
		if ((position += dist) < minRange)
		{
			dist = 1;
		}
	}
}

```

