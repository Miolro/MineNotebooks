#include "include/GameLib/Framework.h"
#include "State.h"
using namespace GameLib;

State* gState = nullptr;
bool initFlag = false;
bool runningFlag = true;

bool gKeyInW = false;
bool gKeyInS = false;
bool gKeyInA = false;
bool gKeyInD = false;


void Framework::update()
{
	unsigned currrentimeStart = time();

	if (!initFlag)
	{
		initFlag = true;
		gState = new State("stageData.txt", "nimotsuKunImage2.dds");
	}

	bool tKeyInW = isKeyOn('w');
	bool tKeyInS = isKeyOn('s');
	bool tKeyInA = isKeyOn('a');
	bool tKeyInD = isKeyOn('d');
	if (tKeyInW && !gKeyInW)
	{
		gState->moveCell('w');
	}
	else if (tKeyInS && !gKeyInS)
	{
		gState->moveCell('s');
	}
	else if (tKeyInA && !gKeyInA)
	{
		gState->moveCell('a');
	}
	else if (tKeyInD && !gKeyInD)
	{
		gState->moveCell('d');
	}

	gKeyInW = tKeyInW;
	gKeyInS = tKeyInS;
	gKeyInA = tKeyInA;
	gKeyInD = tKeyInD;
	gState->drawStateBackground();
	if (gState->drawStateEntity())
	{
		runningFlag = gState->checkGame();
	}
	unsigned currrentimeEnd = time();
	cout << 1000 / currrentimeEnd - currrentimeStart;

}