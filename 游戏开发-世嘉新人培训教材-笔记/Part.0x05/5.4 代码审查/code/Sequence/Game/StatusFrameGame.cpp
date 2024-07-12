#include "StatusFrameGame.h"
#include "Loading.h"
#include "GameLib/GameLib.h"
#include "GameLib/Framework.h"
#include "../StatusFrame.h"
#include "State.h"
#include <sstream>
namespace Sequence {
	StatusFrameGame::StatusFrameGame()
	{
	}
	StatusFrameGame::StatusFrameGame(StatusFrame* frame) :mLoad(nullptr), mState(0)
	{
		mStateId = frame->getStageId();
		mLoad = new Loading();
	}

	StatusFrameGame::~StatusFrameGame()
	{
		SAFE_DELETE(mLoad);
	}

	void StatusFrameGame::update(StatusFrame* frame)
	{
		if (mLoad) {
			mLoad->update(this);
		}
		else if (mState)
		{
			mState->draw(this);

			char keyPut[] = { 'w','s','a','d','q'};
			char keyIn = ' ';
			for (int i = 0; i < 5; i++)
			{	// ����ѭ������
				if (GameLib::Framework::instance().isKeyOn(keyPut[i])) {
					keyIn = keyPut[i];
				};
			}
			if (keyIn != ' ')
			{
				//�����Ƿ�Ϊq  ���ص�����
				if (keyIn=='q')
				{
					frame->setNextStatus(StatusFrame::StatusType::SEQ_STAGE_SELECT);
				}
				mState->move(keyIn);
			}
		}

		switch (nextStatus)
		{
		case Sequence::StatusFrameGame::Status::STA_LOAD:
			GameLib::cout << "����" << GameLib::endl;
			break;
		case Sequence::StatusFrameGame::Status::STA_RUN:
			SAFE_DELETE(mLoad);
			GameLib::cout << "����" << GameLib::endl;
			break;
		case Sequence::StatusFrameGame::Status::STA_CLEAR:
			SAFE_DELETE(mState);
			GameLib::cout << "�������ѡ��" << GameLib::endl;
			frame->setNextStatus(StatusFrame::StatusType::SEQ_STAGE_SELECT);
			break;
		default:
			break;
		}
		nextStatus = StatusFrameGame::Status::STA_NONE;
	}
	void StatusFrameGame::setNextStatus(StatusFrameGame::Status status)
	{
		nextStatus = status;
	}
	void StatusFrameGame::startLoading()
	{
		std::ostringstream oss;
		oss << "data/stageData/" << mStateId << ".txt";
		mState = new State(oss.str().c_str());
	}
}

