#include "GameParent.h"
#include "../Parent.h"

#include "Ready.h"
#include "GameLib/GameLib.h"
namespace Sequence
{
	namespace Game
	{
		GameParent::GameParent()
		{
			mChild = new Ready();
		}
		GameParent::~GameParent()
		{
		}
		Base* GameParent::update(Parent* parent)
		{
			Base* _this = this;
			// 如果发生了场景切换就会执行if的代码
			Base* nextChild = mChild->update(this);
			if (nextChild != mChild)
			{
				// 可以正常转型表示下一个场景继承的是Game::GameChild
				Game::GameChild* castChild = dynamic_cast<Game::GameChild*>(nextChild);
				if (castChild)
				{
					SAFE_DELETE(mChild);
					mChild = castChild;
				}
				else
				{
					// 不属于当前GameChild的派生类那么就会交给上面的Parent处理
					// 如果不能正常转型那表示切换了parent然后就会去找parent的类型转换去切换场景
					_this = nextChild;
				}
				castChild = 0;
			}
			nextChild = 0;
			return _this;
		}
	}
}
