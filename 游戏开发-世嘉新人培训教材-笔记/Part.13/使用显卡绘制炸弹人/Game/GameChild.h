#pragma once
#include "../Sequence/Base.h"

namespace Game
{
	class Parent;
	class GameChild :public Base
	{
	public:
		virtual ~GameChild();
		virtual Base* update(Game::Parent*) = 0;
		Base* update(Base*); // ±»×ÓÀà¼Ì³Ð
		
	};
}


