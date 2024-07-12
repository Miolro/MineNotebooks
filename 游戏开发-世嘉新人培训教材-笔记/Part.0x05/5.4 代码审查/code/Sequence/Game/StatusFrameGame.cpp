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
			{	// 按键循环监听
				if (GameLib::Framework::instance().isKeyOn(keyPut[i])) {
					keyIn = keyPut[i];
				};
			}
			if (keyIn != ' ')
			{
				//过滤是否为q  返回到标题
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
			GameLib::cout << "加载" << GameLib::endl;
			break;
		case Sequence::StatusFrameGame::Status::STA_RUN:
			SAFE_DELETE(mLoad);
			GameLib::cout << "运行" << GameLib::endl;
			break;
		case Sequence::StatusFrameGame::Status::STA_CLEAR:
			SAFE_DELETE(mState);
			GameLib::cout << "清除返回选关" << GameLib::endl;
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

