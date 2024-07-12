#pragma once
#include "Child.h"
#include "GameLib/Input/Manager.h"
#include "GameLib/Input/Keyboard.h"
class Parent;

namespace Sequence
{
	class Title :public Child
	{
	public:
		Child* update(Parent*);
		~Title();
		//GameLib::Input::Manager mManager;
		//GameLib::Input::Keyboard mKeyboard;
	};
}
