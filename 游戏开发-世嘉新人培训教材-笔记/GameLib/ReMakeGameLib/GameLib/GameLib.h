#ifndef INCLUDE_GAMELIB_H
#define INCLUDE_GAMELIB_H
#include <Windows.h>
#include <cstdio>
namespace GameLib
{
	enum Exception
	{
		EXCEPTION_IGNORE,
		EXCEPTION_EXIT,
	};
	void halt(const char* filename, int line, const char* message) {
		char buf[8192];
		sprintf_s(buf, 8192, "%s:%d : %s", filename, line, message);

		MessageBoxA(0, buf, "Critical Error!", MB_OK | MB_ICONERROR);
		//马上结束
		*reinterpret_cast<int*>(0) = 0;
	}

}
// 传入错误信息
#define STRONG_ASSERT( exp ) ( ( !! ( exp ) ) || ( GameLib::halt( __FILE__, __LINE__, #exp ), 0 ) ) //这行不好理解
#endif // !INCLUDE_GAMELIB_H

