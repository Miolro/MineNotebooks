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

## 1.7 补充内容:引用

<font class="tip">C++中有一个引用（reference）的概念，简单的说就是取一个别名</font>

<font class="tip">以下的例子证明了a的别名叫refa，a是5时refa也是5，当refa被修改成6时a也被修改成了6</font>

```C++
	int a = 5;
	int& refa = a;
	std::cout << refa;

	refa = 6;
	std::cout << a;
```

## 1.7.1 引用和指针

<font class="tip">对比：</font>

`创建`

```C++
	int a = 5;
	int& refa = a;  // 引用  不需要获取到数值的地址
	int* ptra = &a; // 指针  需要使用&获取到数值的地址
```

`使用`

```C++
	refa = 10;    // 引用  不需要添加*号赋值
	*ptra = 10;   // 指针  需要添加*号赋值
```

`初始化`

<font class="understanding">其实也很好理解,我不知道你本人的名字,所以没办法凭空给你取别名,因为我连你本人是谁长什么样子都不知道</font>

```C++
    int* ptr;  // 可以初始化
    int& ref;  // 无法初始化  编译报错
```

`不能变更指向的位置`

<font class="understanding">不是很能理解笔者表达的意思</font>

```C++
	int a;
	int& refa = a;
	std::cout << &refa << std::endl;

	int b;    // b的地址??
	refa = b; // 因为b未初始化所以编译报错了
	std::cout << &refa << std::endl;  

    // 下面的代码没有这样的情况
	int c;
	int* ptrc = &c;
	std::cout << &c << std::endl;
	std::cout << ptrc << std::endl;   // 这里的地址表示c的地址

	int d;
	ptrc = &d;
	std::cout << &d << std::endl;
	std::cout << ptrc << std::endl;  // 这里变更了指针指向的位置这个指向的是d
```

`无法使用下标索引和数字加法`

<font></font>

```C++
	int a = 0;
	int* aptr = &a;
	aptr[3] = 2;
	aptr += 2;

	int& aref = a;
	aref[3] = 2;// 在表达式必须包含指向对象的指针类型，但它具有类型 "int"
	aref += 2;
```

<font class="tip">引用可以规避指针操作带来的一系列风险，他因为他必须初始化</font>

```C++
    class A
    {
    public:
        void calc(int* a);
        void calc(int& a);
    };

    void A::calc(int* a)
    {
        *a += 2;
    }
    void A::calc(int& a)
    {
        a += 2;
    }

```

## 1.7.2 用于改善新能的指针和引用

<font class="tip">在这个例子中规避了复制对象中的数据带来的性能损耗</font>\
<font class="tip">但是另外一方面如果使用指针直接操作会修改原对象,为了防止直接修改原对象需要添加const关键词，但是指针在笔者手中`多次强调危险性`,总之在前面几章中可以随意修改标记为私有成员变量的数值可见指针的威力</font>\
<font class="tip">欸~所以我们换用引用能不去用指针就不去用指针,为保证原数据不修改需要像指针一样加上const</font>

```C++
    class A
    {
    public:
        int calc(const int* a);
        int calc(const int& a);
    };

    int A::calc(const int* a)
    {
        int reta = 0;
        reta = *a + 2;
        return reta;
    }
    int A::calc(const int& a)
    {
        int reta = 0;
        reta = a + 2;
        return reta;
    }    

```

```C++
    int main()
    {
        A aClass;
        int a = 2;
        std::cout << aClass.calc(&a);
        std::cout << aClass.calc(a);
    }
```