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

## 1.6 补充内容：指针和内存

<font class="tip">指针是C/C++的指针</font>

## 1.6.1 内存的数组结构

<font class="understanding">单元格的指针=起始地址+偏移地址</font>

## 1.6.2 指针是什么

<font class="understanding">如果不是你提醒我去看`NimotsuKunRawMemory`我还不一定绝望，但是看到代码后是真的绝望，我只能说很优秀的内存管理大师</font>

<font class="tip">在这个代码中只创建了一个全局变量 大小为100的`char[]`数组</font>
<font class="tip">数据交换通过零号下标的char来交换数据</font>

`内存地址`

<font class="tip">内存数组的小标索引又称为内存地址(memory address) 存储该下标的变量叫指针(pointer)</font>
<font class="tip">多看多理解</font>
<font class="tip">强制修改类中的值挺有意思</font>
<font class="tip">可以使用debug断点停下来看看b的值已经变成5了</font>

```C++
    #include <iostream>
    class A {
    private:
        char a;
        char b;
    public:
        void sout();
    };
    void A::sout() {
        std::cout << a << b << std::endl;
    }


    int main()
    {
        A a;
        char* p = reinterpret_cast<char*> (&a);
        *(p + 1) = 5; // p是
        a.sout();
    }

```

<font class="tip">虽然是有意思，但是需要避免这样的指针操作，这样的操作可能会导致bug，这是需要留意的</font>

## 1.6.3 指针和数组

<font class="tip">下面这样表示数组零号下标的下一个元素</font>

```C++
    m[1]=0;
// 等价于
    char* p = &m[0]; //使用&获取到m的起始指针
    *(p+1) = 0;      //使用*把地址转换为存储单元的值 *(p+1)其实和m[1]已经差不多了

// 在C++中也允许
    char* p = &m[0];
    p[1] = 0;

```

`数组定义和内容`

```C++
 char[3] p;
```

<font class="tip">程序不会生成三个只存放char的内存，实际上只是在内存中寻找了一片内存空白区域，然后再开始的地址上插上p这个定位，然后把这个定位发回给</font>

`书中用了一个非常抽象的理解 不愧为char[100]存数据的抽象大师`\
`因为存放地址的变量是一个指针 所以数组的变量就是一个指针`\
<font class="tip">因为变量是指针所以是指针</font>

<font>b省略了寻找空白区域并将其地址保存到变量的过程，b并未存放可以用的内存地址，在使用前要对b进行赋值</font>\
<font class="tip">数组变量是</font>`一开始就被初始化过的指针`


```C++
    char* b;
```

## 1.6.4 值为0的指针

<font class="tip">值为0意味着只想的是内存数组的第一个元素，这是不允许的</font>\
<font>这会导致空指针报错:</font>`引发了异常: 写入访问权限冲突。
p 是 nullptr。` \
<font class="tip">在指针销毁后，值可能还留在旧的位置，如果在次调用这个指针就会访问不该访问的位置</font>\
<font class="tip">书中例子：我搬了家如果电话不换电话会打给下一个住我旧家的人，而不是打给住在新家的我，如果想要打给我就需要把家换掉的同时把电话给换掉(这里的电话指座机)</font>

## 1.6.5 指针类型

<font>其实只是规定距离下一个内存的偏移距离char偏移1  int偏移4</font>

```将p中地址变为T类型大小的两倍```\
???没有测试出结果
```C++
    address+=sizeof(T)*2;

```%

## 1.6.6 new和delete

<font class="tip">`new`:在内存中寻找空白位置，然后把这个位置的索引存入指针；然后就是调用构造函数</font>\
<font class="tip">`delete`:调用析构函数然后释放内存</font>\

`只要传入一个合适的下标值就能强行访问对应位置就像之前的那个会出现bug的程序一样`

## 1.6.7 数组和new的区别

```C++
    int p[5];
    int* p = new int[5];
```
<font class="understanding">new必须在编译时确定内存大小，和函数结束时必须释放内存</font>\
<font class="tip">new的速度会比直接int p[]慢</font>\
<font class="tip">在查找区域和返回索引的方面两者相同</font>

## 1.6.8 关于指针的小结

<font class="tip">指针就是内存数组的地址索引</font>


