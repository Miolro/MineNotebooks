#include "Title.h"
#include <iostream>

#include "GameLib/GameLib.h"
#include "GameOver.h"

namespace Sequence
{

	Child* Title::update(Parent* parent)
	{
		GameLib::Input::Manager mManager = GameLib::Input::Manager::instance();
		GameLib::Input::Keyboard mKeyboard = mManager.keyboard();
		GameLib::cout << "Title" << GameLib::endl;
		// ¿Õ¸ñ´¥·¢ÇÐ»»³¡¾°×´Ì¬
		if (mKeyboard.isTriggered(' '))
		{
			Child* next = new GameOver();
			return next;
		}

		return this;
	}
	Title::~Title()
	{

	}
}

