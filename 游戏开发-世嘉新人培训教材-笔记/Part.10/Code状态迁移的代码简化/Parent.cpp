#include "Parent.h"

#include "Sequence/Child.h"

#include "Sequence/Title.h"
#include "Sequence/Ending.h"
#include "Sequence/GameOver.h"
#include "GameLib/GameLib.h"
Parent::Parent() :mChild(0), mNextChild(0)
{
	mNextChild = mChild = new Sequence::Title();

}

Parent::~Parent()
{
}

void Parent::update()
{
	mNextChild = mChild->update(this);  // 直接按照当前派生类更新

	// 检查状态是否变更
	if (mNextChild != mChild)
	{
		// 删除老的对象并把新对象放入
		SAFE_DELETE(mChild);
		mChild = mNextChild;
	}
}
