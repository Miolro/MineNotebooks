#pragma once
#include "GameChild.h"
namespace Sequence
{
	namespace Game
	{
		class Ready:public GameChild
		{
		public:
			Base* update(GameParent*);
			~Ready();
		};
	}
}