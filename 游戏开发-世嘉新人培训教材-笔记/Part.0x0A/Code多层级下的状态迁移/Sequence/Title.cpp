#include "Title.h"
#include <iostream>

#include "GameLib/GameLib.h"

#include "game/GameParent.h"

namespace Sequence
{

	Base* Title::update(Parent* parent)
	{
 		GameLib::Input::Manager mManager = GameLib::Input::Manager::instance();
		GameLib::Input::Keyboard mKeyboard = mManager.keyboard();
		GameLib::cout << "Title" << GameLib::endl;
		// ¿Õ¸ñ´¥·¢ÇÐ»»³¡¾°×´Ì¬
 		if (mKeyboard.isTriggered(' '))
		{
			Base* next = new Game::GameParent();
			return next;
		}

		return this;
	}
	Title::~Title()
	{

	}
}

