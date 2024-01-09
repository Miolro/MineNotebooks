#include <iostream>
#include "GameLib/Framework.h"
#include "GameLib/GameLib.h"

#include "Sequence/Parent.h"

namespace GameLib
{
	bool isInit = false;
	Sequence::Parent* gParent;

	void Framework::update()
	{
		if (!isInit)
		{
			gParent = new Sequence::Parent();
			isInit = true;
		}
		gParent->update();
	}
}