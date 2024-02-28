#include "Loading.h"
#include "GameLib/GameLib.h"
#include "GameLib/Framework.h"
#include "../Utils/Image.h"
#include "Play.h"
namespace Game
{
	Loading::Loading() :mStated(false)
	{
		GameLib::cout << "Create Title" << GameLib::endl;
		mBackground = new Image("data/dummy.dds");

	}

	Loading::~Loading()
	{
		SAFE_DELETE(mBackground);
	}
	Base* Loading::update(Game::Parent* parent)
	{
		//GameLib::cout << "Upload Loding" << GameLib::endl;
		if (!mStated)
		{
			parent->parentLoadState();
			mStated = true;
		}
		mBackground->drawTexture(640, 480);
		if (waitTarget > 60 * 3)
		{
			return new Play();
		}
		GameLib::Framework::instance().drawDebugString(56, 24, "Loaing.....");
		waitTarget++;
		return this;
	}
}