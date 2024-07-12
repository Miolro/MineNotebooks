#pragma once
#include "GameChild.h"
namespace Game
{ 
	class Parent;
	class Play:public GameChild
	{
	public:
		// Í¨¹ý GameChild ¼Ì³Ð
		Play();
		~Play();
		Base* update(Game::Parent*);
	};
}


