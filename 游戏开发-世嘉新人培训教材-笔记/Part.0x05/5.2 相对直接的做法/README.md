# 5.2相对直接的做法

我们可以使用 系统自带的画图软件在里面写下主题画面 之后保存并用dds转换工具转为dds 将图片显示到主题画面中\
所以问应该怎么切换画面呢

## 5.2.1利用if判断

最简单的方法就是找一个变量来表示是否为主页面,每次通过if语句来区分

```c++
    bool gIsTitleSequence;
```

```c++
    void Framework::updata()
    {
        if(gIsTitleSequence)
        {
            title();
        }else
        {
            game();
        }
    }

```

## 5.2.2使用switch

```c++
    enum Sequence
    {
        SEQUENCE_TITLE,
        SEQUENCE_GAME
    };

    Sequence sequence;

    void Framework::update()
    {
        switch (sequence)
        {
            case SEQUENCE_TITLE:title(); break;
            case SEQUENCE_GAME:game(); break;
        }
    }
```

`注意break以免发生bug`

可以从书中了解到离开主页面时调用主页面时销毁主页面然后创建游戏界面，反之一样

`必要时才创建,非必要时释放`
