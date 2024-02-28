#include "GameParent.h"
#include "GameLib/GameLib.h"
#include "Loading.h"
#include "State.h"
namespace Game
{
	Parent::Parent()
	{
		GameLib::cout << "Parent" << GameLib::endl;
		mChild = new Loading();
	}
	Parent::~Parent()
	{
		SAFE_DELETE(mState);
	}
	Base* Parent::update(Sequence::Parent*)
	{
		//GameLib::cout << "Update Parent" << GameLib::endl;
		Base* _this = this;
		Base* nextChild = mChild->update(this);
		if (nextChild != mChild)
		{
			//同级移动
			Game::GameChild* castnext = dynamic_cast<Game::GameChild*>(nextChild);
			if (castnext)
			{
				SAFE_DELETE(mChild);
				mChild = castnext;
				castnext = 0;
			}
			else // 需要处理不是同级移动的状况  默认返回自己表示还在同级更新  如果走到了这里表示场景不是在这个parent场景下面了
			{
				_this = nextChild;
			}
			nextChild = 0;
		}
		return _this;
	}
	bool Parent::parentLoadState()
	{
		int stateId = 1;
		mState = new Game::State(stateId);
		return false;
	}
	State* Parent::getState() const
	{
		return mState;
	}
}