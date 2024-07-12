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
			// ��������˳����л��ͻ�ִ��if�Ĵ���
			Base* nextChild = mChild->update(this);
			if (nextChild != mChild)
			{
				// ��������ת�ͱ�ʾ��һ�������̳е���Game::GameChild
				Game::GameChild* castChild = dynamic_cast<Game::GameChild*>(nextChild);
				if (castChild)
				{
					SAFE_DELETE(mChild);
					mChild = castChild;
				}
				else
				{
					// �����ڵ�ǰGameChild����������ô�ͻύ�������Parent����
					// �����������ת���Ǳ�ʾ�л���parentȻ��ͻ�ȥ��parent������ת��ȥ�л�����
					_this = nextChild;
				}
				castChild = 0;
			}
			nextChild = 0;
			return _this;
		}
	}
}
