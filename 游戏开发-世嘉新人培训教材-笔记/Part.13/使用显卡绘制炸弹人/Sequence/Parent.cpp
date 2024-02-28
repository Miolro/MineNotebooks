#include "Parent.h"
#include "GameLib/GameLib.h"
#include "BaseChild.h"
#include "Title.h"
namespace Sequence {
	Parent* Parent::mInstance = nullptr;
	void Parent::create()
	{
		ASSERT(!mInstance); // ������������ظ��������жϳ���
		mInstance = new Parent();
	}
	void Parent::destory()  // ������ȥ���������������������ڲ����Ӷ���
	{
		ASSERT(mInstance);
		SAFE_DELETE(mInstance);
	}
	Parent* Parent::instance()
	{
		return mInstance;
	}
	void Parent::update()
	{
		// Child <==> Parent ����͸�����Խ��н���
		Base* nextChild = mChild->update(this);// ���·��ص�ǰ���������������
		// ��ͬ����ȥ�����ǲ��Ǽ̳�ͬһ������ ��Ϊ�Ƕ���ĵ��������  ���û����ô�ͻ�ֱ���ж�
		if (nextChild != mChild)
		{
			Child* child = dynamic_cast<Child*>(nextChild);
			ASSERT(child);
			SAFE_DELETE(mChild);
			mChild = child;
		}
		nextChild = 0;
	}
	Parent::Parent() :mChild(0)
	{
		// ����������ó�ʼ����
		mChild = new Title();
		
	}
	Parent::~Parent()
	{
		SAFE_DELETE(mChild);
	}

}


