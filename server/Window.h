
#pragma once
#include "framework.h"


#define WM_SOCKET WM_USER + 1

class Window {
public:
	Window(HINSTANCE hInstance, int nCmdShow);

	void CreateClass();
	void Init(HINSTANCE hInstance, int nCmdShow);
	void Update();

	HWND hWnd;
private:
	HINSTANCE hInstance;
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};