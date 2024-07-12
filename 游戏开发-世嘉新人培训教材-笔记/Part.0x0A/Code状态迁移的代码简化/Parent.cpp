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
	mNextChild = mChild->update(this);  // ֱ�Ӱ��յ�ǰ���������

	// ���״̬�Ƿ���
	if (mNextChild != mChild)
	{
		// ɾ���ϵĶ��󲢰��¶������
		SAFE_DELETE(mChild);
		mChild = mNextChild;
	}
}
