#include "StatusFrame.h"
#include "Title.h"
#include "StageSelect.h"
#include "GameLib/Framework.h"
namespace Sequence {
	StatusFrame::StatusFrame() :mTitle(nullptr), mGame(nullptr), mStage(nullptr), mNextStatus(StatusType::SEQ_NONE)
	{
		// ��Ҫ��ʼ����ǰ�����еĳ���
		// ����ĳ��� 
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
		// ״̬Ǩ��
		switch (mNextStatus)
		{
		case Sequence::StatusFrame::StatusType::SEQ_STAGE_SELECT:
			GameLib::cout << "ѡ��" << GameLib::endl;
			SAFE_DELETE(mTitle);
			mStage = new StageSelect();
			break;
		case Sequence::StatusFrame::StatusType::SEQ_TITLE:
			GameLib::cout << "����" << GameLib::endl;
			break;
		case Sequence::StatusFrame::StatusType::SEQ_GAME:
			GameLib::cout << "��Ϸ" << GameLib::endl;
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