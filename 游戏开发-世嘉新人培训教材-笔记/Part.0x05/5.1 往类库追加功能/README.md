# 5.1往类库追加功能

## 5.1.1获取输入功能

只获取按下去第一帧的按键

``` c++
 bool Framework::isKeyTreggered(int)const;
```

## 5.1.2帧率相关的功能

- previousFrameInterval()返回前一帧消耗的时间
- frameRate()通过最近60帧算出平均帧
- setFrameRate()设置帧率自动设置sleep

```C++
 class Framework{
    int previousFrameInterval() const;
    int frameRate() const;
    void setFrameRate(int);
 }
```

## 便携的宏定义

- SAFE_DELETE 简化删除对象操作

```C++
    #define SAFE_DELETE( x ) { delete ( x ); ( x ) = 0; }
```

- SAFE_DELETE_ARRAY 简化删除对象数组操作

```c++
    #define SAFE_DELETE_ARRAY( x ) { delete[] ( x ); ( x ) = 0; }
```

- ASSERT 断言传入值为0是中断
  
```c++
    //判断调试和发布的分支
    #ifndef NDEBUG
    #define ASSERT( exp ) ( ( !! ( exp ) ) || ( GameLib::halt( __FILE__, __LINE__, #exp ), 0 ) )
    #else //NDEBUG
    #define ASSERT( exp )
    #endif //NDEBUG
```

- STRONG_ASSERT  断言传入值为0是中断Release下可以运行

```c++
    #define STRONG_ASSERT( exp ) ( ( !! ( exp ) ) || ( GameLib::halt( __FILE__, __LINE__, #exp ), 0 ) ) //这行不好理解
```

- HALT  程序终止

```c++
    #define HALT( exp ) { GameLib::halt( __FILE__, __LINE__, #exp ); }
```
