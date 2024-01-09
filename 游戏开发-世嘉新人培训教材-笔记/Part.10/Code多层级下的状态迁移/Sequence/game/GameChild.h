#pragma once
#include "../Base.h"
namespace Sequence
{
	namespace Game
	{
		class GameParent;
		class GameChild :public Base
		{
		public:
			virtual ~GameChild() {};
			virtual Base* update(GameParent*) = 0;
			Base* update(Base*);
		};
	}
}
