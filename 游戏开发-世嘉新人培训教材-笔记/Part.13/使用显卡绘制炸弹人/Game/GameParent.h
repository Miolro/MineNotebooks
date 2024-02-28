#pragma once
#include "../Sequence/BaseChild.h"
#include "../Sequence/Parent.h"
#include "GameChild.h"
#include "State.h"
namespace Game
{
	class Parent : public Sequence::Child
	{
	public:
		Parent();
		~Parent();
		Base* update(Sequence::Parent*); // ¸¸×Ó´«µÝ
		bool parentLoadState();
		State* getState()const;
	private:
		GameChild* mChild;
		State* mState;
	};
}


