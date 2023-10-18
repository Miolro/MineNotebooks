#include "GameLib/Framework.h"
#include "State.h"

using namespace GameLib;

bool initFlag = false;
State* gState = nullptr;
unsigned* currentLine = new unsigned[10];

void Framework::update()
{
	sleep(1);
	// 需要把当前时间存入到时间轴中  最后一位插入
	currentLine[9] = time();


	//求时间差 0 - 9的时间差
	unsigned differenceTime = currentLine[9] - currentLine[8];
	unsigned differenceTime10 = currentLine[9] - currentLine[0];

	unsigned avg10Fps = 1000 * 10 / differenceTime10;
	cout << avg10Fps << endl;

	if (!initFlag)
	{
		gState = new State("stageData.txt", "nimotsuKunImage2.dds");
		initFlag = true;
	}
	int dx = 0;
	int dy = 0;
	if (isKeyOn('a')) {
		dx -= 1;
	}
	else if (isKeyOn('d')) {
		dx += 1;
	}
	else if (isKeyOn('w')) {
		dy -= 1;
	}
	else if (isKeyOn('s')) {
		dy += 1;
	}
	gState->drawEntity(dx, dy, differenceTime);
	for (int i = 0; i < 9; i++)
	{
		currentLine[i] = currentLine[i + 1];
	}
}