#include "Parent.h"

#include "Child.h"

#include "Title.h"
#include "Ending.h"
#include "GameOver.h"
#include "GameLib/GameLib.h"
namespace Sequence
{
	Parent::Parent() :mChild(0)
	{
		mChild = new Sequence::Title();

	}

	Parent::~Parent()
	{
	}

	void Parent::update()
	{
		 Base* nextChild = mChild->update(this);  // 直接按照当前派生类更新

		// 检查状态是否变更
		if (nextChild != mChild)
		{
			// 这是最上级的处理  如果下级返回的场景无法处理就会进行终止程序处理
			Child* child = dynamic_cast<Child*>(nextChild);
			ASSERT(child);
			// 删除老的对象并把新对象放入
			SAFE_DELETE(mChild);
			mChild = child;
		}
		nextChild = 0;
	}
}
