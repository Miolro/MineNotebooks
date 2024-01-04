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
		//���Ͻ���
		*reinterpret_cast<int*>(0) = 0;
	}

}
// ���������Ϣ
#define STRONG_ASSERT( exp ) ( ( !! ( exp ) ) || ( GameLib::halt( __FILE__, __LINE__, #exp ), 0 ) ) //���в������
#endif // !INCLUDE_GAMELIB_H

