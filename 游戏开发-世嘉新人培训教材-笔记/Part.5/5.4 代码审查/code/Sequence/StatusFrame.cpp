#include "StatusFrame.h"
#include "Title.h"
#include "StageSelect.h"
#include "GameLib/Framework.h"
#include "Game/StatusFrameGame.h"
namespace Sequence {
	StatusFrame::StatusFrame() :mTitle(nullptr), mGame(nullptr), mStage(nullptr), mNextStatus(StatusType::SEQ_NONE)
	{
		// 需要初始化当前容器中的场景
		// 最初的场景 
		mTitle = new Title();
	}

	StatusFrame::~StatusFrame()
	{
		SAFE_DELETE(mTitle);
		SAFE_DELETE(mGame);
		SAFE_DELETE(mStage);
	}

	void StatusFrame::update()
	{
		if (mTitle)
		{
			mTitle->update(this);
		}
		else if (mStage)
		{
			mStage->update(this);
		}
		else if (mGame)
		{
			mGame->update(this);
		}
		// 状态迁移
		switch (mNextStatus)
		{
		case Sequence::StatusFrame::StatusType::SEQ_STAGE_SELECT:
			GameLib::cout << "选关" << GameLib::endl;
			SAFE_DELETE(mTitle);
			SAFE_DELETE(mGame);
			mStage = new StageSelect();
			break;
		case Sequence::StatusFrame::StatusType::SEQ_TITLE:
			GameLib::cout << "标题" << GameLib::endl;
			SAFE_DELETE(mStage);
			SAFE_DELETE(mGame);
			mTitle = new Title();
			break;
		case Sequence::StatusFrame::StatusType::SEQ_GAME:
			GameLib::cout << "游戏" << GameLib::endl;
			SAFE_DELETE(mTitle);
			SAFE_DELETE(mStage);
			mGame = new StatusFrameGame(this);
			break;
		case Sequence::StatusFrame::StatusType::SEQ_NONE:
			break;
		}
		mNextStatus = StatusType::SEQ_NONE;
	}
	void StatusFrame::setStageId(int stageId)
	{
		mStageId = stageId;
	}
	int StatusFrame::getStageId()
	{
		return mStageId;
	}
	void StatusFrame::setNextStatus(StatusType sequenceId)
	{
		mNextStatus = sequenceId;
	}
}