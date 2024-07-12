#pragma once
#include "Base.h"
namespace Sequence {
	class Parent;

	class Child :public Base
	{
	public:
		Base* update(Base*); // Base可以和Child相互转换  状态维持
		virtual ~Child();
		virtual Base* update(Parent*) = 0; // 父子传递
	};
}

