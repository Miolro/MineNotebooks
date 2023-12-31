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
## 1.4 C++课堂
## 1.4.1 命名空间

<font class="tip">书中用了同名但是班级不同的人来打比方</font>\
<font class="understanding">
我自己重新理解一下:
在我们村有两个名字一样的人，他们都叫李华，
刚好他们都在你前面这时你叫了其中一个人的名字，此时两个人看向你，这时就非常尴尬，如果你加上特征，比如说谁谁谁家的李华这是就能正确的叫出对方，然后得到回应
</font>\
<font class="tip">一旦使用using namespace 那么就会作用于全局 所有关于这个头文件引用的包都会被影响</font>\
<font class="understanding">这个就很像JAVA在引入包的时候  这个类就默认使用的就是你引入的那个包，如果想要别的包需要标上包名</font> 

<details>
<summary>代码</summary>

```C++
    namespace Grade1{
        namespace Class2{
            // 一年级二班王同学;
            Student wang;
        }
    }
    namespace Grade2{
        namespace Class2{
            // 二年级二班王同学;
            Student wang;
        }
    }

    Grade1::Class2::wang;
    Grade2::Class2::wang;

```

</details>

## 1.4.2 模板

<font class="tip">`SomeClass`类似于函数的参数，如果写成T那么memberNumber的类型就是T类型的</font>\
<font class="tip">如果使用template去创建前面的intArray2D那么不止可以生成int类型的数据还可以生成其他类型的数组</font>\
<font class="understanding">书中说的看得到指包含`(include)`了这个函数</font>\
<font class="tip">所有的模板`声明和实现都必须写在头文件`中</font>

<details>
<summary>代码</summary>

```C++
    template <class SomeClass> class A
    {
        public:
            SomeClass memberNumber;
    }

```

```C++
    A<int> aInt;
    int bInt = 5;
    aInt.memberNumber = bInt;

    A<float> aInt;
    float bInt = 5.f;
    aInt.memberNumber = bInt;

```

</details>

## 1.4.3 构造函数和析构函数

<font class="tip">构造函数：在对象`创建`时自动调用</font>\
<font class="tip">析构函数：在对象`销毁`时自动调用</font>

<details>
<summary>代码</summary>

```C++

    void foo()
    {
        T t; // 构造函数
        T* tp = new T; // 构造函数
        delete tp;  // 析构函数
    }

```
```C++
    class T
    {
        T();
        T(int a);
        ~T();
    }

```
```C++
    T::T()
    {
        cout<<"初始化T"<<endl;
    }
    T::T(int a)
    {
        cout<<"带参数初始化"<<endl;
    }
    T::~T()
    {
        cout<<"销毁对象"<<endl;
    }
```
<font class="tip">完整示例代码</font>

```C++

    #include <iostream>

    class T
    {
    public:
        T();
        T(int a);
        ~T();
    };

    T::T()
    {
        std::cout << "Create T Object" << std::endl;
    };
    T::~T() {
        std::cout << "Destruction T Object" << std::endl;
    }
    int main()
    {
        //T t;
        T* tp = new T;  // 创建后不适用delet就不会去调用析构函数
        delete tp;
    }
```

</details>

## 1.4.4 初始化

<font class="tip">示例代码</font>

<details>
<summary>代码</summary>

```C++
 Foo::Foo()
 {
    memberBar = 0;
 }

```
</details>

<font class="tip">也可以是</font>


<details>
<summary>代码</summary>

```C++
    Foo::Foo():memberBar(0)
    {

    }

```
</details>

<font class="tip">在1.3.3中出现过下面类似的代码</font>\
<font class="tip">初始化时将member2DArray指针初始化，初始化为外部的传入的宽度，初始化外部传入的高度</font>\
<font class="tip">在初始化变量时如果有多个那么使用逗号隔开`(,)`</font>

```C++
    // 对象被创建时
    IntArray2D(int width, int height) :member2DArray(0), memberWidthSize(width), memberHeightSize(height)
    {
        member2DArray = new int[memberWidthSize * memberHeightSize];
    }

```

<font class="tip">const修饰的常量在class中初始化一旦进入构造函数就不能再修改  如果以上面那种形式来初始化依然是可以初始化常量的</font>

<font class="understanding">会提示你this->studentId=id;表达式必须是可修改的左值	
</font>

<details>
<summary>代码</summary>

```C++
    #include <iostream>
    class Student
    {
    public:
        const int studentId;
        const char* studentName;

        Student(int id, char* name);

    };
    Student::Student(int id, char* name)
    {
        this->studentId = id;
        this->studentName = name;
    }

```
</details>

<font class="understanding">下面使用:的方式可以正常初始化const修饰的常量</font>

<details>
<summary>代码</summary>

```C++
    #include <iostream>

    class Student
    {
    public:
        const int studentId;
        const char* studentName;

        Student(int id, char* name);

    };
    Student::Student(int id, char* name) :studentId(id), studentName(name)
    {

    }

```

</details>

## 1.4.5 成员函数的const

## 1.4.6 两种delete

<font class="tip">delete[]会依次调用各个函数的析构函数，如果对着应该调用delete[]的地方使用delete那么只会调用第一个元素的析构函数</font>\
<font class="tip">需要养成拿了知道放回去的好习惯</font>

## 1.4.7 字符串常量

<font class="tip">C++中内置类型并没有字符串这样的类型</font>\
<font class="tip">上面的baka等同于下面的baka只是简写了</font>\
<font class="tip">本质其实就是一个字符(char)数组，但是在末尾会自动加上一个`\0`所以baka的字符长度是5而不是4</font> 

```C++
	const char baka[] = "baka";
	const char baka[5] = { 'b','a','k','a','\0' };
```
<font class="tip">关于const char* aho = "aho";</font>\
<font class="tip">先创建一个字符数组然后获取到他的第零位指针</font>

```C++
    const char* aho = "aho";

    const char ahoINTRTNAL [4] = {'a','h','o','\0'};
    const char* aho = &ahoINTRTNAL[0];

```