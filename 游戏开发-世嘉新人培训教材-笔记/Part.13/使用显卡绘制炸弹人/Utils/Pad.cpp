#include "Pad.h"

#include "GameLib/Input/Manager.h"
#include "GameLib/Input/Keyboard.h"
#include "GameLib/GameLib.h"
// 进行封装只是为了区分是哪一个玩家输入的键u
bool Pad::isOn(KeyList keyIn, int playerID)
{
	bool ret = false;
	GameLib::Input::Manager manager = GameLib::Input::Manager::instance();
	GameLib::Input::Keyboard keyboard = manager.keyboard();
	// W,S,A,D,Q,J,K
	int keys[] = { 'w','s','a','d','q','j','k' };
	ret = keyboard.isOn(keys[keyIn]);
	return ret;
}

bool Pad::isTriggered(KeyList keyIn, int playerID)
{
	//GameLib::cout << keyIn << GameLib::endl;
	bool ret = false;
	GameLib::Input::Manager manager = GameLib::Input::Manager::instance();
	GameLib::Input::Keyboard keyboard = manager.keyboard();
	// W,S,A,D,Q,J,K
	int keys[] = { 'w','s','a','d','q','j','k' };
	ret = keyboard.isOn(keys[keyIn]);
	return ret;
}
