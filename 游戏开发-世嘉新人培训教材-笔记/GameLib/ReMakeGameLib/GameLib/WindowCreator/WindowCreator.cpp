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
		STRONG_ASSERT(isMainThread() && "�����������߳��ⶨ��");
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


// ע�ᴰ����
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
	// ���ζ���
	RECT rect;
	rect.left = 0;
	rect.top = 0;

	rect.right = gImpl->mWidth;
	rect.bottom = gImpl->mHeight;
	// ͨ����ʼ�Ĵ��ڴ�С��λ�ü��ϴ�����ʽ����ȡת�����λ�úʹ�С
	AdjustWindowRect(&rect, WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX, FALSE);
	// ?? ��Ҫ����ʱ���Բ�һ��
	rect.right -= rect.left;
	rect.bottom -= rect.top; //�����
	rect.left = 0;
	rect.top = 0;
	HWND hWnd;
	hWnd = CreateWindow(szWindowClass, szTitle, WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT, rect.right, rect.bottom, NULL, NULL, hInstance, NULL);
	// ��ʼ��ʧ�ܻ᷵��0x00000000
	if (!hWnd)
	{
		/* ԭ�д����ϲ��� �������᷵�ش������*/
		DWORD errorCode = GetLastError();
		char buffer[sizeof("ErrorCode:") + sizeof(DWORD) + 1];
		sprintf_s(buffer, "ErrorCode:%d", errorCode);
		MessageBoxA(NULL, buffer, "InitInstance Error", MB_OK | MB_ICONERROR);
		/* ԭ�д����ϲ��� �������᷵�ش������*/

		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	// �����ھ�������������
	gImpl->mWindowHandle = hWnd;

	return TRUE;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//  �������ֵ�ƺ�ûʲô��  ��ʼ���߳�ģʽ
	HRESULT hResult = CoInitializeEx(NULL, COINIT_MULTITHREADED);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow);

	MSG msg = {};
	HACCEL hAcceclTable;

	gImpl = new Impl();
	gImpl->mCommandLine = lpCmdLine;
	WindowCreator wc;
	// ����title��class
	memcpy(szTitle, wc.title(), wc.titleLength());
	memcpy(szWindowClass, wc.clazz(), wc.clazzLength());

	RegiserWinClass(hInstance);  // ����ע��

	// ��ʼ������
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}
	HWND hWnd = gImpl->mWindowHandle;
	// ���ٱ�??  �ȼ�
	hAcceclTable = LoadAcceleratorsA(hInstance, MAKEINTRESOURCE(109));
	// ��Ϣ����  ���ڼ�������  ���ڹر�  ������С��.....
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
		// �����źź��鴰���Ƿ��Ѿ��ر�
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
				// ������´��벻֪����������
				//wc.update();
			}
			catch (Exception e)
			{
				if (e == EXCEPTION_EXIT)
				{
					MessageBoxA(NULL, "WindowCreator Error", "�رմ��ڵ���û�а취����ִ�и��´���", MB_OK | MB_ICONERROR);
				}
			}
		}
	}
	return 0;
}