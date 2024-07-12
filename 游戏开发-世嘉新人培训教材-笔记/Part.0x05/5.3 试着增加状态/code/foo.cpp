#include "GameLib/Framework.h"
#include "File.h"
#include "Image.h"
#include "State.h"
#include "Title.h"

namespace GameLib
{
	void showTitle();
	void mainLoop();
	//void debugCoutStatus();

	int rateCount = 0;
	int titleRead = 0;
	State* gState = nullptr;

	enum class stateStatus
	{
		INIT,
		READY,
		CLEAR
	};
	enum class gameStatus {
		RUNNING,
		STOP,
		MENU
	};
	stateStatus gStateStatus = GameLib::stateStatus::INIT;
	gameStatus gStatus = GameLib::gameStatus::MENU;

	void Framework::update()
	{
		//debugCoutStatus();
		setFrameRate(60);
		//if (rateCount % 60 == 0)
		//{
		//	cout << frameRate() << endl;
		//}

		switch (gStatus)
		{
		case GameLib::gameStatus::RUNNING:
			mainLoop();
			if (isKeyTriggered(' '))
			{
				gStatus = GameLib::gameStatus::STOP;
			}
			break;
		case GameLib::gameStatus::STOP:
			if (isKeyTriggered(' '))
			{
				titleRead = 0;
				gStatus = GameLib::gameStatus::RUNNING;

			}
			break;
		case GameLib::gameStatus::MENU:
			break;

		}
	}
	void mainLoop()
	{
		// ������Ϸ����
		switch (gStateStatus)
		{
		case GameLib::stateStatus::INIT:
			gStateStatus = GameLib::stateStatus::READY;
			gState = new State("stageData.txt"); // �ؿ��ļ���ȡ
			break;
		case GameLib::stateStatus::READY:
			gState->draw();
			if (GameLib::Framework::instance().isKeyOn('w'))
			{
				gState->move('w');
			}
			else if (GameLib::Framework::instance().isKeyOn('s'))
			{
				gState->move('s');
			}
			else if (GameLib::Framework::instance().isKeyOn('a'))
			{
				gState->move('a');
			}
			else if (GameLib::Framework::instance().isKeyOn('d'))
			{
				gState->move('d');
			}
			if (gState->gameOver())
			{
				gStateStatus = GameLib::stateStatus::CLEAR;
			}
			break;
		case GameLib::stateStatus::CLEAR:
			SAFE_DELETE(gState);
			GameLib::Framework::instance().requestEnd();
			break;
		}
	}
	void showTitle()
	{
		if (titleRead == 0) {
			Image titleImg = Image("title.dds");
			unsigned* vram = Framework::instance().videoMemory();
			unsigned width = Framework::instance().width();
			int titleWidth = titleImg.getWidth();
			int titleHeight = titleImg.getSize() / titleWidth;
			titleImg.draw(0, 0, 0, 0, titleWidth, titleHeight);
			titleRead = 1;
		}
	}
	void debugCoutStatus()
	{
		switch (gStatus)
		{
		case GameLib::gameStatus::RUNNING:
			cout << "����:";
			break;
		case GameLib::gameStatus::STOP:
			cout << "ֹͣ:";
			break;
		case GameLib::gameStatus::MENU:
			cout << "�˵�:";
			break;
		default:
			break;
		}
		switch (gStateStatus)
		{
		case GameLib::stateStatus::INIT:
			cout << "��ʼ��" << endl;
			break;
		case GameLib::stateStatus::READY:
			cout << "����" << endl;
			break;
		case GameLib::stateStatus::CLEAR:
			cout << "����" << endl;
			break;
		default:
			break;
		}
	}
}