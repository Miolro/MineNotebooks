#include "StageSelect.h"
#include "../Image.h"
#include "StatusFrame.h"
#include "GameLib/GameLib.h"
namespace Sequence {
	StageSelect::StageSelect()
	{
		mImage = new Image("data/image/stageSelect.dds");
	}
	StageSelect::~StageSelect()
	{
		SAFE_DELETE(mImage);
	}
	void StageSelect::update(StatusFrame* frame)
	{
		mImage->draw(0, 0, 0, 0, mImage->getWidth(), mImage->getHeight());
		int stage = 0;
		char tiggerChars[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
		for (int i = 0; i < sizeof(tiggerChars); i++)
		{
			if (GameLib::Framework::instance().isKeyTriggered(tiggerChars[i]))
			{
				stage = i;
			};

		}
		frame->setStageId(stage);
		frame->setNextStatus(StatusFrame::StatusType::SEQ_GAME);
	}
}