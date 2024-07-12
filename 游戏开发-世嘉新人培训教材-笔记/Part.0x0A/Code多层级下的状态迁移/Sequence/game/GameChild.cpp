#include "GameChild.h"
#include "GameParent.h"
#include "GameLib/GameLib.h"
namespace Sequence
{
	namespace Game
	{
		Base* GameChild::update(Base* basePtr)
		{
			GameParent* parent = dynamic_cast<GameParent*>(basePtr);
			ASSERT(parent);
			return update(parent);
		}
	}
}