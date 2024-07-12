#include "Ready.h"
#include "GameLib/GameLib.h"
#include "GameLib/Input/Manager.h"
#include "GameLib/Input/Keyboard.h"

#include "../Title.h"
namespace Sequence
{
	namespace Game
	{
		Base* Ready::update(GameParent* parent)
		{
			GameLib::cout << "Ready" << GameLib::endl;
			GameLib::Input::Manager manager = GameLib::Input::Manager::instance();
			GameLib::Input::Keyboard keyboard = manager.keyboard();

			if (keyboard.isTriggered(' '))
			{
				return new Title();
			}
			return this;
		}
		Ready::~Ready()
		{
		}
	}
}