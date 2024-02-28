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
		// 炸弹的坐标  书中这个属性是放在动态对象中  测试60帧情况下最多放置14个炸弹  所以目前设置14个炸弹容量
		int mBakudanX[BAKUDANPOOL];
		int mBakudanY[BAKUDANPOOL];
		Image* mImage;
		DynamicObject* dyObject;

	};
}


