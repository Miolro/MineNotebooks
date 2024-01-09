#include "Child.h"
#include "Parent.h"
#include "GameLib/GameLib.h"

namespace Sequence
{
	Base* Child::update(Base* basePtr)
	{ 
		Parent* parent = dynamic_cast<Parent*>(basePtr);
		ASSERT(parent);
		return update(parent);
	}
}
