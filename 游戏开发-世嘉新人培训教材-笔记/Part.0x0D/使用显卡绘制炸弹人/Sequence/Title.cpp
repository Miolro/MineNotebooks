#include "Title.h"
#include "../Utils/Pad.h"
#include "GameLib/GameLib.h"
#include "../Game/GameParent.h"
//#include "../Utils/Pad.h"

namespace Sequence
{
	unsigned cursorNumber = 0;
	Title::Title()
	{
		GameLib::cout << "Create Title" << GameLib::endl;
		mBackground = new Image("data/dummy.dds");

	}

	Title::~Title()
	{
		SAFE_DELETE(mBackground);
	}
	Base* Title::update(Parent*)
	{
		//GameLib::cout << "Update Title" << GameLib::endl;
		mBackground->drawTexture(640, 480);
		if (Pad::isTriggered(Pad::W))
		{
			cursorNumber = 0;
		}
		else if (Pad::isTriggered(Pad::S))
		{
			cursorNumber = 1;
		}
		else if (Pad::isTriggered(Pad::J))
		{
			return new Game::Parent();
		}

		GameLib::Framework::instance().drawDebugString(1, 2, "one player");
		GameLib::Framework::instance().drawDebugString(1, 3, "two players");
		GameLib::Framework::instance().drawDebugString(0, 2 + cursorNumber % 3, ">");

		return this;
	}
}