#include "../Child.h"
namespace Sequence
{
	class Parent;
	namespace Game
	{
		class GameChild;
		class GameParent :public Sequence::Child
		{
		public:
			GameParent();
			~GameParent();
			Base* update(Parent*);
		private:
			GameChild* mChild;
		};

	}
}