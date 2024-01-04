#ifndef INCLUDE_GAMELIB_FRAMEWORK_H
#define INCLUDE_GAMELIB_FRAMEWORK_H

namespace GameLib
{
	class Framework
	{
	public:
		Framework();
		void update();
		static Framework instance();
		int width();
		int height();
		unsigned* videoMemory();
		void requestEnd();
		bool isRequestEnded() const;

		void start(void* windowHandle);
		void preUpdate();
		void postUpdate();
		static void create();
		static void destory();
	};
}

#endif