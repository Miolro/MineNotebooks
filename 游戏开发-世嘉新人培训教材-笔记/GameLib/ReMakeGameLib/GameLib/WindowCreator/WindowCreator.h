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
		// 全屏信号
		void enableFullScreen(bool flag)const;
		class Configuration
		{
			void setTitle(const char* title);

			void setWidth(int width);
			void setHeight(int height);

			void enableFullScreen(bool flag);
		};
	};
}
#include "../GameLib.h"
#endif // !INCLUDE_GAMELIB_WINDOWCREATOR_H
