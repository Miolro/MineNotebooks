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
			Impl() :mWidth(640), mHeight(480), mFullScreen(false), mTitle("RemakeFramework"), mWindowCLass("RemakeFramework"), mEndRequest(false), mFullScreenForbidden(false), mStarted(false), mMinimized(false), mActive(false)
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
			bool mFullScreenForbidden; // ��ֹ����
			bool mStarted;
			RECT mRect;
			bool mMinimized;
			bool mActive;
			/*�Ƿ�����ȫ��*/
			void enableFullScreen(bool flag)
			{
				if (mFullScreen != flag) // �������ֵ�Ƿ�ͬ ������ȫ����ʱ��С��״̬��ô���ó�ȫ��״̬Ȼ��������ڴ�СΪȫ����С
				{
					if (mStarted) // ����Ƿ��������е�״̬
					{
						LONG style;
						if (flag) // �����ȫ��״̬����С��״̬
						{
							style = WS_POPUP | WS_VISIBLE;
							GetWindowRect(mWindowHandle, &mRect);
							SetWindowLongPtr(mWindowHandle, GWL_STYLE, style);  // �������õ���SetWindowLong(hwnd,GWL_STYLE,style)
							SetWindowPos(mWindowHandle, NULL, 0, 0, mWidth, mHeight, SWP_SHOWWINDOW);
						}
						else
						{
							style = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;
							SetWindowLong(mWindowHandle, GWL_STYLE, style);
							SetWindowPos(mWindowHandle, NULL, mRect.left, mRect.top, mRect.right - mRect.left, mRect.bottom - mRect.top, SWP_SHOWWINDOW);
						}
					}
					mFullScreen = flag;
				}
			}
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

	void WindowCreator::enableFullScreen(bool flag)const
	{
		// ȥ���� gImpl�е�ȫ������
		gImpl->enableFullScreen(flag);
	}

	void WindowCreator::Configuration::setTitle(const char* title)
	{
		gImpl->mTitle = title;
	}

	void WindowCreator::Configuration::setWidth(int width)
	{
		gImpl->mWidth = width;
	}
	void WindowCreator::Configuration::setHeight(int height)
	{
		gImpl->mHeight = height;
	}

	void WindowCreator::Configuration::enableFullScreen(bool flag)
	{
		gImpl->enableFullScreen(flag);
	}

	/*ender{}ender*/
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE: // ���ڹر�ʱ����ִ�����
		gImpl->mEndRequest = true;
		break;
	case WM_DESTROY: // ����DestroyWindowʱ�������
		PostQuitMessage(0);
		break;
	case WM_SYSKEYDOWN:
		// �Ƿ��ֹ����  // ��Ҫ��ѹALT����ѹENTER��
		std::cout << "1" << std::endl;
		if (!gImpl->mFullScreenForbidden && wParam == VK_RETURN)
		{
			if (gImpl->mFullScreen)
			{
				WindowCreator().enableFullScreen(false);
			}
			else
			{
				WindowCreator().enableFullScreen(true);
			}
		}
		return DefWindowProc(hWnd, msg, wParam, lParam);
	case WM_SYSCOMMAND: // ���ڿؼ�ִ�� ���ֱ�ӻ��Ϊȫ��....��֪��ΪʲôҪ�������
		if (wParam == SC_MAXIMIZE)
		{
			if (!gImpl->mFullScreenForbidden)
			{
				WindowCreator().enableFullScreen(true); // ���ʱ��Ҫ����DefWindowProc
			}
		}
		else if (wParam == SC_MINIMIZE)
		{
			gImpl->mMinimized = true;
			gImpl->mActive = false;
			DefWindowProc(hWnd, msg, wParam, lParam);
		}
		else if (wParam == SC_RESTORE)
		{
			gImpl->mMinimized = false;
			gImpl->mActive = true;
			DefWindowProc(hWnd, msg, wParam, lParam);
		}
		else
		{
			DefWindowProc(hWnd, msg, wParam, lParam);
		}
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
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
	gImpl->mStarted = true; // ѭ�������ź�
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