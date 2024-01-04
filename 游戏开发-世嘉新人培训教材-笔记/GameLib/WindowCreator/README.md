# WindowCreator.cpp

## Impl的作用

作用1:用于管理类的默认变量和全局变量\
作用2:使用匿名保护放置类外的函数来修改这个类中的值

下面的Impl():后的是需要给定的默认值

[WindowSDK](https://learn.microsoft.com/zh-cn/previous-versions/visualstudio/visual-studio-2012/bb384843(v=vs.110))

## 启动位置和代码

hInstance: 应用程序的当前实例的句柄。\
hPrevInstance: 上一个实例的句柄\
lpCmdLine: 指向窗口命令行的指针\
nCmdShow :控制窗口的显示方式。 此参数可以是可在 ShowWindow 函数的 nCmdShow 参数中指定的任何值。

[Windows SDK 在泛型、 Windows 代码页和 Unicode 版本中提供函数原型](https://learn.microsoft.com/zh-cn/windows/win32/intl/conventions-for-function-prototypes)

关于为什么入口函数不叫WinMain去找了一下资料,当使用不同的字符集时设置的启动入口也会不同

Unicode时 例如使用wchar_t类型时 函数入口是`wWinMain`

```C++
#include<window.h>
#define _UNICODE
int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow);
```

使用多字符集时 例如使用char类型时 函数入口是`WinMain`

```C++
#include<window.h>
#define MBCS
int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPTSTR lpCmdLine,int nCmdShow);
```

使用多字符集时 使用tchar.h后 函数入口是`_tWinMain`所以为什么启动使用的是_tWinMain

```C++
#include	<tchar.h>
#include	<windows.h>
int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
```

## 窗口注册

MyRegisterClass( hInstance );\
定义窗口的结构体  [详细参考微软文档](https://learn.microsoft.com/zh-cn/windows/win32/api/winuser/ns-winuser-wndclassexa?redirectedfrom=MSDN)

WNDCLASSEX 结构类似于 WNDCLASS 结构。 有两个区别。 WNDCLASSEX 包括 cbSize 成员（指定结构的大小）和 hIconSm 成员，该成员包含与窗口类关联的小图标的句柄。

```C++
typedef struct tagWNDCLASSEXA {
  UINT      cbSize;     // 此结构的大小（以字节为单位）。 将此成员设置为 sizeof(WNDCLASSEX)。 在调用 GetClassInfoEx 函数之前，请务必设置此成员。
  UINT      style;      // 类样式 () 。 此成员可以是 类样式的任意组合。
  WNDPROC   lpfnWndProc;    // 指向窗口过程的指针。 必须使用 CallWindowProc 函数调用窗口过程。 有关详细信息，请参阅 WindowProc。
  int       cbClsExtra;     // 要根据窗口类结构分配的额外字节数。 系统将字节初始化为零。
  int       cbWndExtra;     // 在窗口实例之后分配的额外字节数。 系统将字节初始化为零。 如果应用程序使用 WNDCLASSEX 注册使用资源文件中的 CLASS 指令创建的对话框，则必须将此成员设置为 DLGWINDOWEXTRA。
  HINSTANCE hInstance;      // 实例的句柄，该实例包含类的窗口过程。
  HICON     hIcon;          // 类图标的句柄。 此成员必须是图标资源的句柄。 如果此成员为 NULL，则系统会提供默认图标。
  HCURSOR   hCursor;        // 类游标的句柄。 此成员必须是游标资源的句柄。 如果此成员为 NULL，则每当鼠标移动到应用程序的窗口中时，应用程序都必须显式设置光标形状。
  HBRUSH    hbrBackground;  // 类背景画笔的句柄。 此成员可以是用于绘制背景的画笔的句柄，也可以是颜色值。 颜色值必须是以下标准系统颜色之一， (值 1 必须添加到所选颜色) 。 如果提供了颜色值，则必须将其转换为以下 HBRUSH 类型之一：
  LPCSTR    lpszMenuName;   // 指向以 null 结尾的字符串的指针，该字符串指定类菜单的资源名称，因为名称显示在资源文件中。 如果使用整数来标识菜单，请使用 MAKEINTRESOURCE 宏。 如果此成员为 NULL，则属于此类的窗口没有默认菜单。
  LPCSTR    lpszClassName;  // 指向以 null 结尾的字符串或 的指针是原子。 如果此参数是 atom，则它必须是先前调用 RegisterClass 或 RegisterClassEx 函数创建的类 atom。 原子必须位于 lpszClassName 的低序字中;高序字必须为零。
  HICON     hIconSm;        // 与窗口类关联的小图标的句柄。 如果此成员为 NULL，系统会在 hIcon 成员指定的图标资源中搜索要用作小图标的适当大小的图标。
} WNDCLASSEXA, *PWNDCLASSEXA, *NPWNDCLASSEXA, *LPWNDCLASSEXA;
```

## 窗口创建

InitInstance( hInstance, nCmdShow )\
其中包含窗口全屏设置 窗口位置设置  窗口创建  显示窗口  更新窗口\
当穿件成功时会往全局的Impl属性管理类中写入窗口句柄

```C++
ATOM RegisterWindow(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	/*Class styles*/
	wcex.style = CS_VREDRAW | CS_HREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = NULL;
	wcex.hCursor = NULL;
	wcex.hbrBackground = NULL;
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szClassName;
	wcex.hIconSm = NULL;
	return RegisterClassEx(&wcex);
}

```

初始化窗口信息

```C++
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
```

## 窗口事件处理

lpfnWndProc

```C++
LRESULT CALLBACK WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, Msg, wParam, lParam);
}
```

通过message获取到状态枚举

## 部分宏

忽略这个未使用的传参使他不报错

```C++
UNREFERENCED_PARAMETER(args)
```

## 系统API

用于初始化线程,设置并发模型

```C++
CoInitializeEx( NULL, COINIT_MULTITHREADED );
```

通过初始的窗口大小和位置加上窗口样式来获取转化后的位置和大小

```C++
AdjustWindowRect(&rect, WS_ACTIVECAPTION, FALSE);
```

枚举参数

```C++
typedef enum tagCOINIT {
  COINIT_APARTMENTTHREADED = 0x2, // 初始化单元线程对象并发的线程 (请参阅备注) 。
  COINIT_MULTITHREADED,	// 初始化多线程对象并发的线程 (请参阅备注) 。
  COINIT_DISABLE_OLE1DDE = 0x4, // 禁用 DDE 以支持 OLE1。
  COINIT_SPEED_OVER_MEMORY = 0x8  // 增加内存使用量，以尝试提高性能。
} COINIT;

```
| 返回代码           | 说明                                                                                                                           |
| ------------------ | ---------------------------------------------------------------------------------------------------------------------------- |
| S_OK               | COM 库在此线程上已成功初始化。                                                                                                   |
| S_FALSE            | COM 库已在此线程上初始化。                                                                                                       |
| RPC_E_CHANGED_MODE | 先前对 CoInitializeEx 的调用将此线程的并发模型指定为多线程单元 (MTA) 。 这也可能表明发生了从中性线程单元到单线程单元的更改。                   |
