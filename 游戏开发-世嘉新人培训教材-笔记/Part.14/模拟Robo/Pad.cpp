#include "Pad.h"
#include "GameLib/Input/Manager.h"
#include "GameLib/Input/Keyboard.h"
using namespace GameLib;
Pad* Pad::mInstance = 0;
Pad* Pad::instance()
{
	return mInstance;
}

void Pad::create()
{
	// 如果没有进行初始化类  实例没有被创建
	if (!mInstance)
	{
		mInstance = new Pad();
	}
}

void Pad::destory()
{
	if (mInstance)
	{
		delete(mInstance);
		mInstance = nullptr;
	}
}

bool Pad::isOn(Button button, int playerId)
{
	Input::Manager manager = Input::Manager::instance();
	Input::Keyboard key = manager.keyboard();
	char inputKey = 0;
	switch (button)
	{
	case Pad::KEY_FORWARD:
		inputKey = 'w';
		break;
	case Pad::KEY_BACK:
		inputKey = 's';
		break;
	case Pad::KEY_LEFT:
		inputKey = 'a';
		break;
	case Pad::KEY_RIGHT:
		inputKey = 'd';
		break;
	case Pad::KEY_FLY:
		inputKey = ' ';
		break;
	}
	return key.isOn(inputKey);
}

bool Pad::isTriggered(Button button, int playerId)
{
	return false;
}

Pad::~Pad()
{
}

Pad::Pad() {

}