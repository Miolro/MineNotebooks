#pragma once
namespace Sequence {
	class Child;
	class Parent
	{
	public:
		static Parent* instance(); // ·µ»Ø×Ô¼º
		static void create();
		static void destory();
		void update();
	private:
		Child* mChild;
		static Parent* mInstance;
		Parent();
		~Parent();
	};
}
