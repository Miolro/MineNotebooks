#pragma once
#include "Child.h"

class Parent;

namespace Sequence
{
	class GameOver :public Child
	{
	public:
		GameOver();
		~GameOver();
		Child* update(Parent*);
	private:

	};

}
