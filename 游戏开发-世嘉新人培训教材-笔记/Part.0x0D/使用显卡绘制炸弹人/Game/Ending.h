#pragma once
#include "GameChild.h"
class Image;

namespace Game
{
	class Ending:public GameChild
	{
		public:
		// ͨ�� GameChild �̳�
		Ending();
		~Ending();
		Base* update(Game::Parent*);
	private:
		Image* mBackground;
	};
}

