# 第九章 各种输入设备

省流：主要介绍新加库的使用

通过键盘鼠标手柄设备输入,这里删除了原有Framework中的键盘输入而由InputDevices取代`之前的代码可能无法运行`

## 9.1 获取输入设备实例

本章引入具有Input名称空间的Input模块来负责输入处理

Input模块中有名为Manager的单例类，负责管理键盘 鼠标 手柄 三种输入设备


代码中三种设备分别对应三个类，档Manager收到获取键盘的请求时，返回一个Keyboard类实例

## 9.2 键盘

可运行代码
```C++
#include "GameLib/Framework.h"
#include "GameLib/Input/Manager.h"
#include "GameLib/Input/Keyboard.h"
using namespace GameLib::Input;

namespace GameLib
{
	void Framework::update()
	{

		Manager manager = Manager::instance();  // 获取管理类实例
		Keyboard keyboard = manager.keyboard(); // 然后来用管理类来获取键盘
		if (keyboard.isOn('a'))
		{
			GameLib::cout << "a" << GameLib::endl;
		}
	}
}
```

## 9.3鼠标

Mouse类实例

```C++
#include "GameLib/Framework.h"
#include "GameLib/Input/Manager.h"
#include "GameLib/Input/Mouse.h"

using namespace GameLib::Input;

namespace GameLib
{
	void Framework::update()
	{

		Manager manager = Manager::instance();
		Mouse mouse = manager.mouse();

		if (mouse.isOn(Mouse::BUTTON_LEFT))
		{
			GameLib::cout << "鼠标左键" << GameLib::endl;
		};
	}
}
```

## 9.4 手柄

报错了？？

```C++
ASSERT( i >= 0 && i < gManagerImpl->mJoystickNumber );
```

## 9.5 在《炸弹人》游戏中使用手柄

### 9.5.1 关于类库封装

### 9.5.2 示例代码

代码看书这里略

将需要用到的按键封装到一个枚举中这样就做到了信息隐藏，然后就就是涉及到是哪个输入设备发出的信号只要关心调用哪个库即可