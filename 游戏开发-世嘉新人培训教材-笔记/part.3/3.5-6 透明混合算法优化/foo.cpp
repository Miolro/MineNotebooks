#include "GameLib/Framework.h"
#include "State.h"

// ȫ�ֵĳ�����Ϣ
State* gState = nullptr;
// ��ʼ����ʶ
bool gInit = false;


namespace GameLib
{
	void Framework::update()
	{
		if (!gInit)
		{
			gInit = true;
			// ����Ҫ���ļ��л�ȡ��ͼ��Ϣ
			gState = new State("./resources/stageData.txt");

		}
		else
		{
			char inputKey;
			cin >> inputKey;
			gState->moveCell(inputKey);
			// �������
			if (gState->checkGame())
			{
				Framework::requestEnd();
			}

		}

		cout << "info" << endl;
	}
}