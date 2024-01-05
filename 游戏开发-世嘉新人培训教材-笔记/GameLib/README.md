# 研究时的疑问

WindowCreator启动在gImpl中加载其他model

``` text
Q: 为什么启动使用Framework::update()
A1: 实际上并不是这里启动  而是Framework是一个其中的一个Model我们只是处理了这块拓展出来的更新方
法,这就解释了在之前找了半天看到这个update在头文件中是一个未实现的方法
A2: 启动位置实际在WindowCreator中的_tWinMain中
```

``` text
Q: 如何实现窗口的更新/循环更新
A1: 窗口更新使用一个死循环来定义,里面有一个mEnd判断如果没结束就会进入到wc.update()函数更新
A2: 具体的更新函数在Framework中的WindowCreator::update()虽然调用的WindowCreator但是内部还是有执行一个叫f.update的方法
这里更新的就是你写的拓展方法具体调用流程
WindowCreator启动->进入while(true)死循环->wc.update()更新->Framework文件中的WindowCreator::update()方法->调用f.update()方法更新
```
