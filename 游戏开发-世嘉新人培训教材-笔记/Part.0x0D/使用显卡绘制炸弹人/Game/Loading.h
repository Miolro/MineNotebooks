#include "GameChild.h"
#include "GameParent.h"
#include "../Utils/Image.h"
namespace Game
{
	class Loading:public Game::GameChild
	{
	public:
		Loading();
		~Loading();
		 Base* update(Game::Parent*); // ¸¸×Ó´«µÝ
	private:
		int waitTarget = 0;
		Image* mBackground;
		bool mStated;
	};
}
