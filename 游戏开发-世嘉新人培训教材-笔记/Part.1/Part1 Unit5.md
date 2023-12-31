<style>
   
    .tip{
        color:#ff9000
    }

    .understanding{
        color:#84C9EF      
    }
    .default{
        color:#88ACBC 
    }

</style>

# 第一章
## 1.5 补充内容：标志位和位运算

## 1.5.1 标志位

<font class="tip">标志位又称flag也就是旗帜的意思</font>\
<font class="tip">但是游戏往往会通过一个无符号的整型`(unsigned int)`来表示和管理多个标志位一个无符号int一共有4字节 那么就有4*8个比特位 也就是32bit可以同时管理32个表示位</font>\
<font class="tip">由于32位过长而且8位的unsigned也能表示状态  所以用unsigned char来说明下面的信息</font>

## 1.5.2 标志位的存储


```C++
    00110101
```

<font tip="tip">下面是封装标志的检测的代码</font>

```C++
    class Flag
    {
        // 检测标志位状态
        bool check() const;
        // 设置标志位为有效
        void set();
        // 设置标志位为无效
        void reset();

    public:

    private:
        unsigned char mFlag;
    };

```

## 1.5.3 使用普通计算获取标志位状态

<font class="tip">现实中并不是所有表示情况都是按照0和1这样排布的，而往往会是像十进制这样，虽然在计算机中处理仍然通过二进制处理</font>\
<font class="tip">我们需要找到一种可以检测任意二进制位上是0或者1的办法</font>

`最直接的方法`

<font class="tip">现在是否为墙壁和是否为目的地两个信息存入标志位变量中</font>\
<font class="tip">最左边用于保存墙壁标志位,第二位用于保存是否是目的地</font>\
<font class="tip">所以可以通过数值是否大于128来判断这个二进制位是否是1，但是不能通过数值是否大于64来判断第二位是否为1</font>\
<font class="tip">书上说的很直白，既然没办法判断64位上是否是1那我直接减掉128（排除最左边的数）然后再去做判断就能知道64这个位置上是否位1</font>

```C++
    // 传入一个十进制的数
    unsigned char t = mFlags;
    // 判断值是不是大于128 是就减掉128
    if(t>=128){
        t-=128;
    }
    // 最后判断这个mFalgs上64这个位上的值是1还是0
    return (t>=64) ? true:false;
```

<font class="tip">上面的方法很繁琐  光是判断两位已经写了这么多代码 如果需要判断其他六位那么会变得很臃肿,所以需要优化一下</font>

`使用除法`

<font class="tip">下面的代码类似于上面的代码都是用来判断64位上是否为1</font>
```C++
    // 传入一个十进制的数 64为上有值
    // 如果传入128
    unsigned char t = 64+128;
    // 除去一个64获得一个商为3
    // 出去一个64得到一个商为2
	t /= 64;
    // 用商去乘128 溢出截断 unsigned长度为255 得到的3*128-256 = 128 
    // 用商区乘128 溢出截断 2*128-256 = 0
	t *= 128;
	std::cout << (t != 0);
```

```C++
    #include <iostream>
    class Flag
    {
    public:
        // 检测标志位状态
        bool check(unsigned char f) const;
        // 设置标志位为有效
        void set();
        // 设置标志位为无效
        void reset();

    private:
        unsigned char mFlag = 128 + 32 + 16 + 8 + 4 + 2 + 1;
    };
    bool Flag::check(unsigned char f)const {
        unsigned char t = mFlag;
        t /= f;
        t *= 128;
        return (t != 0) ? true : false;
    }

    enum Flags
    {
        FLAG_WALL = 128,
        FLAG_GOAL = 64
    };
    int main()
    {
        Flag flag;
        std::cout << flag.check(FLAG_WALL);

    }

```

## 1.5.4 乘除法运算和位移

```C++
    t=(t<<n);
    t <<= n;
```

`用位移操作改写`

```C++
enum Falg
{
    FLAG_WALL=7;
    FLAG_GOAL = 6;
};
```

<font class="tip">先移动f位 f位右边的位数  然后左移7次 把f挪到第8位</font>

```C++
bool FLag::check (unsigned char f)
{
    unsigned char t = mFlags;
    t>>=f;
    t<<7;
    return (t!=0)?true:false;
}
```

## 1.5.5 使用位运算

<font class="tip">and运算</font>


```C++
	//  0000 0100 = 0000 0101 and 1000 0110
    unsigned char flag3 = 0x06 & 0x05;
```

<font class="tip">在汇编语言第四版王爽中有这么一个操作不使用判断符号去修改字符串，将小写的变为大写或者将大写的字符串变为小写</font>\


## 1.5.6 设置标志位为有效

<font class="tip">or运算</font>

```C++
	//  0000 0111 = 0000 0101 and 1000 0110
    unsigned char flag3 = 0x06 | 0x05;
```

<font class="tip">小写的a是(97)大写A是(65)相差32</font>\
<font class="tip">所以只需要设置第32位位1就可以转小写</font>\
<font class="tip">通过OR就可以设置指定位置为1</font>

```C++
    // 0110 0001 = 0100 0001 | 0010 0000
    unsigned char flag3 = 0x41 | 0x20;
```

<font class="tip">xor运算</font>

```C++
	//  0000 0011 = 0000 0101 and 1000 0110
    unsigned char flag3 = 0x06 ^ 0x05;
```

## 1.5.7 将标志位设置为无效

<font class="tip">原理是通过修改bit位高位第2位来修改大小写</font>\
<font class="tip">小写的a是(97)大写A是(65)相差32</font>\
<font class="tip">所以只需要设置第32位位0就可以转大写</font>

```C++
    // 0100 0001 = 0110 0001 and 1101 1111
    unsigned char flag3 = 0x61 & 0xDF;
```

<font class="tip">取反操作</font>\
<font>xor 11111111 或者 ~数值</font>

```C++
    // 0110 0001 xor 1111 1111 = 1001 1110
    unsigned char flag3 = 0x61 ^ 0xff;
    // 使用xor 1111 1111 反转一次再使用~来反转得到原来的值  0x61
    flag = ~flag3
```

## 1.5.8 一次性操作多个标志位

## 1.5.9 十六进制数

<font>很遗憾C++不支持二进制表达 但是允许使用十六进制表达0x开头为16进制</font>