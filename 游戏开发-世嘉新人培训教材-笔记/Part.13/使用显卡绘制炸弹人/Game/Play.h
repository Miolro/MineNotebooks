#pragma once
#include "GameChild.h"
namespace Game
{ 
	class Parent;
	class Play:public GameChild
	{
	public:
		// ͨ�� GameChild �̳�
		Play();
		~Play();
		Base* update(Game::Parent*);
	};
}


