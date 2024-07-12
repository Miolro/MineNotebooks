#include "GameChild.h"
#include "GameParent.h"
#include "GameLib/GameLib.h"
namespace Game
{
	GameChild::~GameChild()
	{
	}
	// parent��ָ�������һ���Parent Ҳ����GameParent
	Base* GameChild::update(Base* parentPtr)
	{
		Game::Parent* parent = dynamic_cast<Game::Parent*>(parentPtr);
		ASSERT(parent);
		return update(parent);
	}
}