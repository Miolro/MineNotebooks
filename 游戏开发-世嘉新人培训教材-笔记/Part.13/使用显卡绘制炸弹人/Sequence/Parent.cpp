#include "Parent.h"
#include "GameLib/GameLib.h"
#include "BaseChild.h"
#include "Title.h"
namespace Sequence {
	Parent* Parent::mInstance = nullptr;
	void Parent::create()
	{
		ASSERT(!mInstance); // 如果单例对象被重复创建则中断程序
		mInstance = new Parent();
	}
	void Parent::destory()  // 用销毁去调用自身析构函数销毁内部的子对象
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
		// Child <==> Parent 子类和父类可以进行交互
		Base* nextChild = mChild->update(this);// 更新返回当前子类或者其他子类
		// 不同就先去找找是不是继承同一个子类 因为是顶层的的子类对象  如果没有那么就会直接中断
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
		// 这里可以设置初始场景
		mChild = new Title();
		
	}
	Parent::~Parent()
	{
		SAFE_DELETE(mChild);
	}

}


