#pragma once
#include "GameChild.h"
class Image;

namespace Game
{
	class Ending:public GameChild
	{
		public:
		// Í¨¹ý GameChild ¼Ì³Ð
		Ending();
		~Ending();
		Base* update(Game::Parent*);
	private:
		Image* mBackground;
	};
}

