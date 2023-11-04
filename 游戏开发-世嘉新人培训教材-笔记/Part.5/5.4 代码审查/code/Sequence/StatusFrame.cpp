#include "StatusFrame.h"
#include "Title.h"
#include "StageSelect.h"
#include "GameLib/Framework.h"
namespace Sequence {
	StatusFrame::StatusFrame() :mTitle(nullptr), mGame(nullptr), mStage(nullptr), mNextStatus(StatusType::SEQ_NONE)
	{
		// 需要初始化当前容器中的场景
		// 最初的场景 
		mTitle = new Title();
	}

	StatusFrame::~StatusFrame()
	{
	}

	void StatusFrame::update()
	{
		if (mTitle)
		{
			mTitle->update(this);
		}
		else if (mStage) {
			mStage->update(this);
		}
		// 状态迁移
		switch (mNextStatus)
		{
		case Sequence::StatusFrame::StatusType::SEQ_STAGE_SELECT:
			GameLib::cout << "选关" << GameLib::endl;
			SAFE_DELETE(mTitle);
			mStage = new StageSelect();
			break;
		case Sequence::StatusFrame::StatusType::SEQ_TITLE:
			GameLib::cout << "标题" << GameLib::endl;
			break;
		case Sequence::StatusFrame::StatusType::SEQ_GAME:
			GameLib::cout << "游戏" << GameLib::endl;
			SAFE_DELETE(mStage);
			
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
	void StatusFrame::setNextStatus(StatusType sequenceId)
	{
		mNextStatus = sequenceId;
	}
}