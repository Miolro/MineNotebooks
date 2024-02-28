#include "Ending.h"
#include "GameLib/Framework.h"
#include "../Utils/Image.h"
#include "../Utils/Pad.h"
#include "GameParent.h"
#include "../Sequence/Title.h"
namespace Game
{
	Ending::Ending()
	{
		GameLib::cout << "Create Title" << GameLib::endl;
		mBackground = new Image("data/dummy.dds");
	}
	Ending::~Ending()
	{
		SAFE_DELETE(mBackground);
	}
	Base* Ending::update(Game::Parent* parent)
	{
		mBackground->drawTexture(640, 480);
		GameLib::Framework::instance().drawDebugString(56, 24, "END.....PUT KEY:J TO CONTINUE");
		if (Pad::isOn(Pad::W))
		{
			return new Sequence::Title();
		}
		return this;
	}

}