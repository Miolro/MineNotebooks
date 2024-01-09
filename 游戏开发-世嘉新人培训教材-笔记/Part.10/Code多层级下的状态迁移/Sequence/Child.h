#pragma once
#include "Base.h"
namespace Sequence
{
	class Parent;
	class Ending;
	class Title;
	class GameOver;
	class Child :public Base
	{
	public:
		virtual Base* update(Parent*) = 0; // 添加virtual ... =0 标识这个方法在child里本身没有这个方法，但是派生类会有这个方法
		virtual ~Child() {}; // 空的函数  保证可以析构派生类
		Base* update(Base* basePrt);
	};
}
