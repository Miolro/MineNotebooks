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
			//ͬ���ƶ�
			Game::GameChild* castnext = dynamic_cast<Game::GameChild*>(nextChild);
			if (castnext)
			{
				SAFE_DELETE(mChild);
				mChild = castnext;
				castnext = 0;
			}
			else // ��Ҫ������ͬ���ƶ���״��  Ĭ�Ϸ����Լ���ʾ����ͬ������  ����ߵ��������ʾ�������������parent����������
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