#pragma once
#include "StaticObject.h"
#include "DynamicObject.h"
#include "../Utils/Array2DTemp.h"
#include "../Utils/Image.h"
namespace Game
{
	static const int WIDTH = 19;
	static const int HEIGHT = 15;
	static const int LAST_BOOM_TIME = 180;
	static const int SHOCK_WAVES_TIME = 60;
	static const int BAKUDANPOOL = 15;
	class State
	{
	public:
		enum Flag
		{
			RUNNING,
			STOP,
			LOSE,
			CLEAR,
			WIN_PLAYER1,
			WIN_PLAYER2,
		};
		State(int stateId);
		~State();
		void draw();
		State::Flag update();
	private:
		Array2DTemplate<StaticObject> mStaticObjects;
		// ը��������  ������������Ƿ��ڶ�̬������  ����60֡�����������14��ը��  ����Ŀǰ����14��ը������
		int mBakudanX[BAKUDANPOOL];
		int mBakudanY[BAKUDANPOOL];
		Image* mImage;
		DynamicObject* dyObject;

	};
}


