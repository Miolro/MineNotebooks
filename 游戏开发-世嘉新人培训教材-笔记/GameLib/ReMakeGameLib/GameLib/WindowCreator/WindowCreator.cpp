#include "WindowCreator.h"
#include <Windows.h>
#include <string>
#include <iostream>
using namespace std;
using namespace GameLib;

#define MAX_LOADSTRING 100 
TCHAR szTitle[MAX_LOADSTRING];
TCHAR szWindowClass[MAX_LOADSTRING];

namespace GameLib
{
	/*begin{}begin*/
	namespace
	{
		class Impl
		{
		public:
			Impl() :mWidth(320), mHeight(240), mFullScreen(false), mTitle("RemakeFramework"), mWindowCLass("RemakeFramework"), mEndRequest(false)
			{
				mThreadId = GetCurrentThreadId();
			}
			int mWidth;
			int mHeight;
			bool mFullScreen;
			string mTitle;
			string mWindowCLass;
			string mCommandLine;
			DWORD mThreadId;
			HWND mWindowHandle;
			bool mEndRequest;
		};
		Impl* gImpl = nullptr;
	}
	WindowCreator::WindowCreator()
	{
		STRONG_ASSERT(isMainThread() && "不允许在主线程外定义");
	}
	bool WindowCreator::isMainThread()const
	{
		return gImpl->mThreadId == GetCurrentThreadId();
	}
	const char* WindowCreator::title()const
	{
		return gImpl->mTitle.c_str();
	}
	int WindowCreator::titleLength()const
	{
		return static_cast<int>(gImpl->mTitle.size());
	}
	const char* WindowCreator::clazz() const
	{
		return gImpl->mWindowCLass.c_str();
	}
	int WindowCreator::clazzLength() const
	{
		return static_cast<int>(gImpl->mWindowCLass.size());
	}
	bool WindowCreator::isEndRequested()const
	{
		return gImpl->mEndRequest;
	}
	void WindowCreator::requestEnd() const
	{
		gImpl->mEndRequest = true;
	}
	/*ender{}ender*/
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		gImpl->mEndRequest = true;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
}


// 注册窗口类
ATOM RegiserWinClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_VREDRAW | CS_HREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = NULL;
	wcex.hCursor = NULL;
	wcex.hbrBackground = NULL;
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = NULL;

	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	// 矩形对象
	RECT rect;
	rect.left = 0;
	rect.top = 0;

	rect.right = gImpl->mWidth;
	rect.bottom = gImpl->mHeight;
	// 通过初始的窗口大小和位置加上窗口样式来获取转化后的位置和大小
	AdjustWindowRect(&rect, WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX, FALSE);
	// ?? 需要花点时间脑补一下
	rect.right -= rect.left;
	rect.bottom -= rect.top; //计算差
	rect.left = 0;
	rect.top = 0;
	HWND hWnd;
	hWnd = CreateWindow(szWindowClass, szTitle, WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT, rect.right, rect.bottom, NULL, NULL, hInstance, NULL);
	// 初始化失败会返回0x00000000
	if (!hWnd)
	{
		/* 原有代码上补充 如果报错会返回错误代码*/
		DWORD errorCode = GetLastError();
		char buffer[sizeof("ErrorCode:") + sizeof(DWORD) + 1];
		sprintf_s(buffer, "ErrorCode:%d", errorCode);
		MessageBoxA(NULL, buffer, "InitInstance Error", MB_OK | MB_ICONERROR);
		/* 原有代码上补充 如果报错会返回错误代码*/

		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	// 将窗口句柄存入管理类中
	gImpl->mWindowHandle = hWnd;

	return TRUE;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//  这个返回值似乎没什么用  初始化线程模式
	HRESULT hResult = CoInitializeEx(NULL, COINIT_MULTITHREADED);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow);

	MSG msg = {};
	HACCEL hAcceclTable;

	gImpl = new Impl();
	gImpl->mCommandLine = lpCmdLine;
	WindowCreator wc;
	// 设置title和class
	memcpy(szTitle, wc.title(), wc.titleLength());
	memcpy(szWindowClass, wc.clazz(), wc.clazzLength());

	RegiserWinClass(hInstance);  // 窗口注册

	// 初始化窗口
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}
	HWND hWnd = gImpl->mWindowHandle;
	// 加速表??  热键
	hAcceclTable = LoadAcceleratorsA(hInstance, MAKEINTRESOURCE(109));
	// 消息处理  关于键盘输入  窗口关闭  窗口最小化.....
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
		{
			if (GetMessage(&msg, NULL, 0, 0))
			{
				if (!TranslateAccelerator(msg.hwnd, hAcceclTable, &msg))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}
			else
			{
				break;
			}
		}
		// 发出信号后检查窗口是否已经关闭
		if (wc.isEndRequested())
		{
			if (hWnd)
			{
				DestroyWindow(hWnd);
				hWnd = 0;
			}
		}
		else
		{
			try
			{
				// 这个更新代码不知道来自哪里
				//wc.update();
			}
			catch (Exception e)
			{
				if (e == EXCEPTION_EXIT)
				{
					MessageBoxA(NULL, "WindowCreator Error", "关闭窗口但是没有办法继续执行更新代码", MB_OK | MB_ICONERROR);
				}
			}
		}
	}
	return 0;
}