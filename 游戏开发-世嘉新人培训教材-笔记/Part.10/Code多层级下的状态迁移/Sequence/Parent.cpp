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
		 Base* nextChild = mChild->update(this);  // ֱ�Ӱ��յ�ǰ���������

		// ���״̬�Ƿ���
		if (nextChild != mChild)
		{
			// �������ϼ��Ĵ���  ����¼����صĳ����޷�����ͻ������ֹ������
			Child* child = dynamic_cast<Child*>(nextChild);
			ASSERT(child);
			// ɾ���ϵĶ��󲢰��¶������
			SAFE_DELETE(mChild);
			mChild = child;
		}
		nextChild = 0;
	}
}
