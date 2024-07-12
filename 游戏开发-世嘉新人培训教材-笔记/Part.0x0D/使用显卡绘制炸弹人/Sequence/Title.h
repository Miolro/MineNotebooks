#include "BaseChild.h"
#include "../Utils/Image.h"
namespace Sequence
{
	class Title :public Child
	{
	public:
		Title();
		~Title();
		Base* update(Parent*);
	private:
		Image* mBackground;
		Image* mFont;
	};
}