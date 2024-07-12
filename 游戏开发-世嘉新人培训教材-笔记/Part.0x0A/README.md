# 第十章 状态迁移详解

涉及到C++的继承用法

使用的库依然是`InputDevices`

## 10.1 问题定位

if-else的状态判断代码导致格外繁琐

```C++
if (mTitle)
		{
			mTitle->update(this);
		}
		else if (mStage)
		{
			mStage->update(this);
		}
		else if (mGame)
		{
			mGame->update(this);
		}
```

但是上面的代码无论是逻辑和传参基本相同`都是传入一个父级的指针然后子类对父类修改状态来切换`

## 10.2 使用继承

基本逻辑归类，提取代码整合父类

### 10.2.1 基类

 添加virtual ... =0 标识这个方法在child里本身没有这个方法，但是派生类会有这个方法  因为不存在所以无需做代码实现`但派生类有义务实现这个函数，不然引发编译错误` 

File:Child.h

 ```C++
 #pragma once
class Child
{
public:
	virtual void update(Parent*) = 0; 
};
 ```

### 10.2.2 派生类

如何标记Title/GameOver属于Child类

File:Title.h

```C++
#include "Child.h"
class Title:public Child
{
public:
	void update(Parent*);
};
```

Child类派生出 Title类

### 10.2.3 派生类的基类

- 成员
  - 派生类可以拥有成员
  
    ```C++
        Class A
        {
            void foo(){cout<<"foo()"<<endl;}
            int a;
        }
        Class B:public A
        {

        }
        B b;
        b.a = 5;  // b调用a中的属性
        b.foo()   // b调用a中的行为
    ```
- 指针和引用
    ```
    虽然类型可以被转为基类（父类）但是变量指向的对象还是他们的派生类（子类）
    ```

### 10.2.4 虚析构函数

在继承过程中，需要在销毁时留意

在对对象销毁时如果像这样

```C++
	Child* title = new Title();
	delete title;
```

new Title()会生成一个Title对象，此时析构也必须执行title本身的析构函数，但是他只会调用Child的析构函数，而Title本身的析构函数不会调用

解决方法:析构函数也定义为虚函数  `实际操作的时候确实没有调用到派生类的析构` 

## 10.3 实际运用

## 10.4 补充内容:简化状态迁移的代码

`对比代码`

- 旧代码
    ```C++
    void StatusFrame::update()
	{
		if (mTitle)
		{
			mTitle->update(this);
		}
		else if (mStage)
		{
			mStage->update(this);
		}
		else if (mGame)
		{
			mGame->update(this);
		}
		// ״̬Ǩ��
		switch (mNextStatus)
		{
		case Sequence::StatusFrame::StatusType::SEQ_STAGE_SELECT:
			GameLib::cout << "ѡ��" << GameLib::endl;
			SAFE_DELETE(mTitle);
			SAFE_DELETE(mGame);
			mStage = new StageSelect();
			break;
		case Sequence::StatusFrame::StatusType::SEQ_TITLE:
			GameLib::cout << "����" << GameLib::endl;
			SAFE_DELETE(mStage);
			SAFE_DELETE(mGame);
			mTitle = new Title();
			break;
		case Sequence::StatusFrame::StatusType::SEQ_GAME:
			GameLib::cout << "��Ϸ" << GameLib::endl;
			SAFE_DELETE(mTitle);
			SAFE_DELETE(mStage);
			mGame = new StatusFrameGame(this);
			break;
		case Sequence::StatusFrame::StatusType::SEQ_NONE:
			break;
		}
		mNextStatus = StatusType::SEQ_NONE;
	}
    ```
- 新代码
    ```C++

    void mainLoop()
    {
        switch (gNextStatus)
        {
        case Parent::STA_TITLE:  // 主题画面
            SAFE_DELETE(gChild);
            gChild = new Sequence::Title();
            break;
        case Parent::STA_GAMEOVER: // 游戏结束
            SAFE_DELETE(gChild);
            gChild = new Sequence::GameOver();
            break;
        //case Parent::STA_GAME:
        //	// 连接接下去的游戏状态类
        //	SAFE_DELETE(gChild);
        //	gChild = new Sequence::Title();
        //	break;
        case Parent::STA_CLEAR: // 全部通关
            SAFE_DELETE(gChild);
            gChild = new Sequence::Ending();
            break;
        default:
            break;
        }
        gNextStatus = Parent::STA_STAY;
        gChild->update(gParent);  // 直接按照当前派生类更新
    }
    ```

`更新场景时减少了if-else的嵌套`\
`大幅度省略了更新状态的代码量`\
`也不用讲究应该销毁哪个对象`

```C++

```

### 10.4.1 问题的关键

略。。。

### 10.4.2 让职责分配更加合理

主循环代码继续缩减

```C++
void mainLoop()
{
	//switch (gNextStatus)
	//{
	//case Parent::STA_TITLE:  // 主题画面
	//	SAFE_DELETE(gChild);
	//	gChild = new Sequence::Title();
	//	break;
	//case Parent::STA_GAMEOVER: // 游戏结束
	//	SAFE_DELETE(gChild);
	//	gChild = new Sequence::GameOver();
	//	break;
	//	//case Parent::STA_GAME:
	//	//	// 连接接下去的游戏状态类
	//	//	SAFE_DELETE(gChild);
	//	//	gChild = new Sequence::Title();
	//	//	break;
	//case Parent::STA_CLEAR: // 全部通关
	//	SAFE_DELETE(gChild);
	//	gChild = new Sequence::Ending();
	//	break;
	//default:
	//	break;
	//}
	//gNextStatus = Parent::STA_STAY;
	gNextChild = gChild->update(gParent);  // 直接按照当前派生类更新

	// 检查状态是否变更
	if (gNextChild != gChild)
	{
		// 删除老的对象并把新对象放入
		SAFE_DELETE(gChild);
		gChild = gNextChild;
	}
}
```

`主循环已经不再承担更新类状态的工作 转而由派生类转移`

派生类修改

`旧代码`

```C++
void Title::update(Parent* parent)
{
	// 一些普通的更新逻辑  比如打印字符串之类的
}
```

`新代码`

```C++
	Child* Title::update(Parent* parent)
	{
		GameLib::Input::Manager mManager = GameLib::Input::Manager::instance();
		GameLib::Input::Keyboard mKeyboard = mManager.keyboard();
		GameLib::cout << "Title" << GameLib::endl;
		// 空格触发切换场景状态
		if (mKeyboard.isTriggered(' '))
		{
			Child* next = new GameOver();
			return next;
		}

		return this;
	}
```

通过不同的对象来优化掉switch分支

### 10.4.3 示例代码

略 去看我写的源码

## 10.5 补充内容:跨层级的状态迁移处理和改进

主要关注两个Parent的Cpp文件

代码在Code多层级下的状态迁移里面有迁移过程的备注

`正向随便带带`

启动流程 foo->激活parent.cpp的更新->初始化后进入Title.cpp->更新时按空格->这个时候会迁移到GameParent.cpp->初始化Ready->执行update()

`反向详细讲`

Ready.cpp更新时空格切换到Title.cpp->进行一个dynamic_cast<Game::GameChild>->此时的Titlt不属于GameChild管理(派生)的类所以转型失败->转而返回Ready.update()返回的title对象交给Parent处理
->如果上层的Parent可以处理那么就是Child管理的(派生类)那么就执行这个Parent的代码

### 10.5.1 dynamic_cast

可以转换基类和派生类转换成功返回地址不然就会返回空对象(0x00000000)

### 10.5.2 重新定义每个层级的基类

略  看代码

### 10.5.3 示例代码

不同于书中给的迭代出来的代码 这边用更加简单的结构重写了一次

------`base`------`Parent`
|
|-----`Child`-----`Title`
|&nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|---`Game::GameParent`
|
|-----`Game::GameChild`----`Ready`

主题逻辑应该是差不多的只是少了对上级Parent传参

### 10.5.4 使用该方法的必要性(全是吐槽)

吐槽:感谢笔者问候害我脑子宕机了两天

但是不得不说接触没接触过的东西确实让我这个不会用抽象继承的人稍稍感觉到震撼,好用是好用但是理逻辑理起来是真的费脑

读者表示:可以用但是在查缺少实现哪个方法时候找了一下午,第二天发现Ready的update的头文件里少写继承了一个方法,想了半天为什么new 不出GameParent,原来我当时又少继承了一个方法,总之处理这些光报Line:1 xxx.obj挺头疼的

## 10.6 继承原理

略 看会数先
