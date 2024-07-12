#include "GameOver.h"

#include "GameLib/GameLib.h"

namespace Sequence
{
	GameOver::GameOver()
	{
	}

	GameOver::~GameOver()
	{
	}
	Child* GameOver::update(Parent*)
	{
		GameLib::cout << "GameOver" << GameLib::endl;
		return this;
	}
}