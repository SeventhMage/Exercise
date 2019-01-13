#include <windows.h>
#include "GLDriver.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
	{
					 PAINTSTRUCT ps;
					 BeginPaint(hWnd, &ps);
					 EndPaint(hWnd, &ps);
	}
		return 0;
	case WM_ERASEBKGND:
		return 0;

	case WM_SYSKEYDOWN:
	case WM_SYSKEYUP:
		return 0;

	case WM_KEYDOWN:
	{
	}
		return 0;
	case WM_KEYUP:
	{
	}
		return 0;
	case WM_MOUSEWHEEL:
	{
	}
		return 0;
	case WM_SIZE:
	{					
	}
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_SYSCOMMAND:
		// prevent screensaver or monitor powersave mode from starting
		if ((wParam & 0xFFF0) == SC_SCREENSAVE ||
			(wParam & 0xFFF0) == SC_MONITORPOWER ||
			(wParam & 0xFFF0) == SC_KEYMENU
			)
			return 0;

		break;

	case WM_ACTIVATE:
		// we need to take care for screen changes, e.g. Alt-Tab

		break;

	case WM_USER:

		return 0;

	case WM_SETCURSOR:
		// because Windows forgot about that in the meantime


	case WM_INPUTLANGCHANGE:
		// get the new codepage used for keyboard input

		return 0;

	case WM_LBUTTONDOWN:
	{
						 
	}

		return 0;
	case WM_LBUTTONUP:
	{
						
	}
		return 0;
	case WM_LBUTTONDBLCLK:
		return 0;
	case WM_RBUTTONDOWN:
	{
						 
	}
		return 0;
	case WM_RBUTTONUP:
	{
						
	}
		return 0;
	case WM_MOUSEMOVE:
	{
	}
		return 0;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

int main(int argc, char *argv[])
//int __stdcall WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	HINSTANCE hInstance = GetModuleHandle(0);

	const wchar_t* ClassName = L"CWin32Device";
	HWND hWnd;
	HDC hDC;

	// Register Class
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadCursor(NULL, IDC_ARROW);
	wcex.hCursor = LoadCursor(NULL, IDI_APPLICATION);
	wcex.hbrBackground = NULL;// (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = 0;
	wcex.lpszClassName = ClassName;
	wcex.hIconSm = 0;

	// if there is an icon, load it
	wcex.hIcon = (HICON)LoadImage(hInstance, L"", IMAGE_ICON, 0, 0, LR_LOADFROMFILE);

	RegisterClassEx(&wcex);

	// create window
	hWnd = CreateWindow(ClassName, L"", WS_OVERLAPPEDWINDOW, 100, 200,
		960, 640, NULL, NULL, hInstance, NULL);

	hDC = GetDC(hWnd);
	InitWindowDriver(hDC);
	ReleaseDC(hWnd, hDC);

	ShowWindow(hWnd, SW_SHOWNORMAL);
	UpdateWindow(hWnd);

	ShowCursor(TRUE);


	BOOL bQuit = FALSE;
	do 
	{
		MSG msg;
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
				bQuit = TRUE;
		}
		else
		{
			Sleep(100);
		}
	} while (!bQuit);
	
	return 0;
}