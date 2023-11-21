#include <iostream>

#include <SFML/Graphics.hpp>

#include "framework.h"

#include "clientConfig.h"

#include "Menu.h"
#include "Game.h"
#include "Result.h"
#include "ExitButton.h"
#include "NetworkButton.h"
#include "WaitingScreen.h"
#include "GameManager.h"

#include <windows.h>

#include "Resource.h"

using namespace sf;

class Application {
public:
    Application();
    ~Application();
    void Run();

    static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
    void ProcessEvents();
    void Render();
    void Update();

    RenderWindow window;

    clientConfig client;

    Menu menu;
    Game game;
    Result result;
    ExitButton exitButton;
    NetworkButton networkButton;
    WaitingScreen waitingScreen;
};