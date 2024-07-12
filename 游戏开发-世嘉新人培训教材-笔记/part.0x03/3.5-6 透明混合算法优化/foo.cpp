#include "GameLib/Framework.h"
#include "State.h"

// 全局的场景信息
State* gState = nullptr;
// 初始化标识
bool gInit = false;


namespace GameLib
{
	void Framework::update()
	{
		if (!gInit)
		{
			gInit = true;
			// 我需要从文件中获取地图信息
			gState = new State("./resources/stageData.txt");

		}
		else
		{
			char inputKey;
			cin >> inputKey;
			gState->moveCell(inputKey);
			// 结束检测
			if (gState->checkGame())
			{
				Framework::requestEnd();
			}

		}

		cout << "info" << endl;
	}
}