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

## 1.3 添加读取场景数据的功能
<font class="tip">在每次修改地图时都需要去重新修改一次代码然后编译运行，一个可能编译时间很长，第二不方便做地图制作和修改，比如需要制作mod之类的</font>

## 1.3.1 准备
<font class="tip">文件读取通过`ifsteam`实现</font>\
<font class="tip">`ifstream`是C++标准库中的，用于文件读取，需要`#include<fstream>`</font>\
<font class="tip">使用`seekg()`移动到文件末尾，然后通过`tellg()`获取到文件的大小，然后使用返回的`fileSize`来分配内存大小</font>\
<font class="tip">然后一次性`read(读取的文件,单次读取的大小)`</font>\
<font class="tip">可以封装成一个函数，在游戏读取文件的时候基本上不会出现只读一半的情况</font>\
<font class="tip">`ifstream::binary`是一个重要的参数</font>


<details>
<summary>代码</summary>

```c++
    #include <iostream>
    #include<fstream>

    using namespace std;

    int main()
    {
        ifstream inputFile("stageData.txt", ifstream::binary);
        inputFile.seekg(0, ifstream::end);
        int fileSize = static_cast<int>(inputFile.tellg());
        inputFile.seekg(0, ifstream::beg);

        char* fileImage = new char[fileSize];
        inputFile.read(fileImage, fileSize);
        cout.write(fileImage, fileSize);
    }

```

</details>

## 1.3.2 数据格式

<font class="tip">无论什么形式，在最总的表达总会变成枚举类型的数组</font>\
<font class="tip">所以需要一种直观的表现形式比如图文</font>
```
    00000000
    01221310
    01441110
    01111110
    00000000
```

<font class="tip">纯数组对人理解来说`过于抽象`，如果可以理解那倒也是无所谓，为了不那么抽象可以使用字符串或者标志性的文字来区别，因为最后都会变成一个枚举数组，中间处理是必不可少的，所以有了书里的</font>

```
    ########
    # .. p #
    # oo   #
    #      #
    ########
```

上面两个都表示同一个场景但是理解起来容易的多

## 1.3.3 场景大小

<font class="tip">因为状态数组可以通过new动态地按照所需大小创建,所以只需要其他办法把数值传入即可,因为谁也不知道下一张地图宽是多少高是多少的</font>

### 被视为二维数组的一维数组


<details>
<summary>代码</summary>

```C++

    #include<fstream>

    class IntArray2D {
    private:
        const int memberWidthSize = 0;
        const int memberHeightSize = 0;
        int* member2DArray;
    public:
        // 对象被创建时
        IntArray2D(int width, int height) :member2DArray(0), memberWidthSize(width), memberHeightSize(height)
        {
            member2DArray = new int[memberWidthSize * memberHeightSize];
        }
        // 对象被销毁时
        ~IntArray2D()
        {
            delete[]member2DArray;
            member2DArray = 0;
        }
        int& operator() (int x, int y)
        {
            return member2DArray[y * memberWidthSize + x];
        }
        const int& operator()(int x, int y)const
        {
            return member2DArray[y * memberWidthSize + x];
        }

    };

```

</details>

## 1.3.4 错误处理
<font class="tip">错误处理</font>\
<font class="tip">在数据加载时就去检查场景信息，但是这样会使得游戏加载缓慢，对于复杂的游戏来说并不可取</font>\
<font class="tip">通过特定的程序去生成</font>

## 1.3.5 示例代码
<font class="tip">测试读者对C++的熟悉程度</font>
<font class="tip">熟悉的可以跳过C++的基本内容，反正我是都会看的</font>