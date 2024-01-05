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

		// ֹͣ��Ϣ
		bool isEndRequested()const;
		// ����ֹͣ�ź�
		void requestEnd()const;
		// ȫ���ź�
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
