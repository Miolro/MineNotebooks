#ifndef INCLUDE_GAMELIB_WINDOWCREATOR_H
#define INCLUDE_GAMELIB_WINDOWCREATOR_H

namespace GameLib
{
	class WindowCreator
	{
	public:
		WindowCreator();
		bool isMainThread()const;

		const char* title()const;
		int titleLength() const;

		const char* clazz()const;
		int clazzLength() const;

		// 停止信息
		bool isEndRequested()const;
		// 发出停止信号
		void requestEnd()const;
	};
}
#include "../GameLib.h"
#endif // !INCLUDE_GAMELIB_WINDOWCREATOR_H
