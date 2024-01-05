# 研究时的疑问

WindowCreator启动在gImpl中加载其他model

``` text
Q: 为什么启动使用Framework::update()
A1: 实际上并不是这里启动  而是Framework是一个其中的一个Model我们只是处理了这块拓展出来的更新方
法,这就解释了在之前找了半天看到这个update在头文件中是一个未实现的方法
A2: 启动位置实际在WindowCreator中的_tWinMain中
```
