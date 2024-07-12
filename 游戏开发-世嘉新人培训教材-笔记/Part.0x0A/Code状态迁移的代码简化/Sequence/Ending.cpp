#include "Ending.h"

#include "GameLib/GameLib.h"

namespace Sequence
{
	Ending::Ending()
	{
	}

	Ending::~Ending()
	{
	}
	Child* Ending::update(Parent*)
	{
		GameLib::cout << "Ending" << GameLib::endl;
		return this;
	}
}