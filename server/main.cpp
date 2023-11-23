#ifndef UNICODE
#define UNICODE
#endif 

#include "Window.h"

#define WM_SOCKET WM_USER + 1

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    Window window(hInstance, nCmdShow);
    return 0;
}