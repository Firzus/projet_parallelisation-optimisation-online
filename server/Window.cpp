#ifndef UNICODE
#define UNICODE
#endif 
#include "Window.h"
#include "serverConfig.h"
#include "ServeurWeb.h"
//#include <windowsx.h>

const wchar_t CLASS_NAME[] = L"Sample Window Class";
//serverConfig server;
ServeurWeb serverWeb;

Window::Window(HINSTANCE hInstance, int nCmdShow) {
	CreateClass();
	Init(hInstance, nCmdShow);
}

void Window::CreateClass() {
	WNDCLASS wc = { };

	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;

	RegisterClass(&wc);
}

void Window::Init(HINSTANCE hInstance, int nCmdShow) {
	// Create the window.

	hWnd = CreateWindowEx(
		0,                              // Optional window styles.
		CLASS_NAME,                     // Window class
		L"Learn to Program Windows",    // Window text
		WS_OVERLAPPEDWINDOW,            // Window style

		// Size and position
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

		NULL,       // Parent window    
		NULL,       // Menu
		hInstance,  // Instance handle
		NULL        // Additional application data
	);

	serverWeb.Init();
	//server.Init(hWnd);
	if (!hWnd)
	{
		MessageBox(0, L"Failed to Create Window!", 0, 0);
		PostQuitMessage(0);
	}

	//ShowWindow(hWnd, nCmdShow);
	Update();
}

void Window::Update() {
	MSG msg = { };
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
	/*case WM_USER:
		server.HandleSocketMessage(wParam, lParam);*/
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}



