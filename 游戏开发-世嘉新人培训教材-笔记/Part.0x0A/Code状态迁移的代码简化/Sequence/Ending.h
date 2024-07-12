#pragma once
#include "Child.h"

class Parent;

namespace Sequence
{
	class Ending:public Child
	{
	public:
		Ending();
		~Ending();
		Child* update(Parent*);
	private:

	};

}