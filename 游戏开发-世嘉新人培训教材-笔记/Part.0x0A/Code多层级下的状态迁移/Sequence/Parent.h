#pragma once
namespace Sequence {
	class Child;
	class Parent
	{
	public:
		Parent();
		~Parent();
		void update();
	private:

		//GameStaus mStatus;
		Sequence::Child* mChild;					// ����һ����ǰ���ɵ�child
	};
};
