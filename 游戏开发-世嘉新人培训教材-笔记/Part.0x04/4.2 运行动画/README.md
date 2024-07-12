# 第四章实时游戏

`实现按下一个键走格`

```C++
    bool gKeyInW = false;
    bool gKeyInS = false;
    bool gKeyInA = false;
    bool gKeyInD = false;

    if (tKeyInW && !gKeyInW)
    {
        gState->moveCell('w');
    }
    else if (tKeyInS && !gKeyInS)
    {
        gState->moveCell('s');
    }
    else if (tKeyInA && !gKeyInA)
    {
        gState->moveCell('a');
    }
    else if (tKeyInD && !gKeyInD)
    {
        gState->moveCell('d');
    }

    gKeyInW = tKeyInW;
	gKeyInS = tKeyInS;
	gKeyInA = tKeyInA;
	gKeyInD = tKeyInD;

```

## 运行动画

之前的先的枚举类型存储已经不能满足存储要求 现在要将enum Object改为一个enum class来保存更多对象的信息而不仅仅只保存一个属性id

想吐槽一下 从无动画版本改到有动画版本想了两天重写了一堆方法  中间穿插了一堆设置动画创建动画的方法  因为没办法改动原有无动画版本的代码所以我重写了一次也顺便找了在写代码过程中的问题（问题点基本上都在代码中注释）

`某种意义上算是大修`

- 动画莫名其妙从左上角开始(在初始化shifting时候设置成0 每次渲染动画都要从0开始渲染)
- 在显示图片时候发现只能显示一点点(ifstream没加binary)
- 关于渲染没完成就判定游戏结束
- 关于不看书的情况下去设计实体类(这玩意没点思路难写)
- 在我重写Array2D.h时候出了一堆奇奇怪怪的问题
- 重写了绘制cell的方式原先按单元格渲染的已经不能满足按照像素点渲染
- 小人从缺口出跑出地图

## 固定帧率

while循环（busy loop 忙碌等待）
获取n毫秒后的时间戳作为循环结束的标志 之后每次在循环中去获取时间与结束时间做比较相等后跳出循环去执行接下去的语句`while会消耗大量的资源`

因此可以使用sleep()来设置执行频率,在休眠期间cpu消耗低
