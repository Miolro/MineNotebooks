#include <iostream>
#include "GameLib/Framework.h"
#include "GameLib/GameLib.h"

#include "Parent.h"

namespace GameLib
{
	bool isInit = false;
	Parent* gParent;

	void Framework::update()
	{
		if (!isInit)
		{
			gParent = new Parent();
			isInit = true;
		}
		gParent->update();
	}
}