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
		Sequence::Child* mChild;					// 保存一个当前生成的child
	};
};
