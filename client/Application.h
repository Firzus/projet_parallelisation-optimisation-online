#include <iostream>

#include <SFML/Graphics.hpp>
#include "framework.h"

#include "Menu.h"
#include "Game.h"
#include "Result.h"
#include "ExitButton.h"
#include "RestartButton.h"
#include "NetworkButton.h"
#include "WaitingScreen.h"
#include "GameManager.h"

#include <windows.h>

using namespace sf;

enum class ApplicationState {
    Menu,
    Game,
    Result
};

class Application {
public:
    Application();
    virtual ~Application();
    void Run();

private:
    void ProcessEvents();
    void Render();
    void Update();

    RenderWindow window;
    ApplicationState state;

    Menu menu;
    Game game;
    Result result;
    RestartButton restartButton;
    ExitButton exitButton;
    NetworkButton networkButton;
    WaitingScreen waitingScreen;
};