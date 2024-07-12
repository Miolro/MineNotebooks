#include "BaseChild.h"
#include "GameLib/GameLib.h"
#include "Parent.h"

namespace Sequence {
	Base* Child::update(Base* basePtr)
	{
		Parent* parent = dynamic_cast<Parent*>(basePtr);
		ASSERT(parent);
		return update(parent);
	}
	Child::~Child()
	{

	}
}