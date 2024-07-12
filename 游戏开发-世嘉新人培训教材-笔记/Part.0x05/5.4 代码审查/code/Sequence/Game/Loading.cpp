#include "Loading.h"
#include "GameLib/GameLib.h"
#include "StatusFrameGame.h"
#include "../File.h"
#include "../Image.h"
namespace Sequence {
	Loading::Loading() :mWaitTime(0)
	{
		mImage = new Image("data/image/loading.dds");
	}

	Loading::~Loading()
	{
		SAFE_DELETE(mImage);
	}

	void Loading::update(StatusFrameGame* frame)
	{
		if (!mStart)
		{
			frame->startLoading();
			mStart = true;
		}
		else
		{
			if (mWaitTime == 60)
			{
				frame->setNextStatus(StatusFrameGame::Status::STA_RUN);
			}
			mImage->draw(0, 0, 0, 0, mImage->getWidth(), mImage->getHeight());
			mWaitTime++;
		}

	}
}