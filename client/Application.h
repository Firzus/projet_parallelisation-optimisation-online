#include <iostream>
#include "framework.h"
//#include <SFML/Audio.hpp>

#include "Menu.h"
#include "Game.h"
#include "Result.h"
#include "MusicButton.h"
#include "ExitButton.h"
#include "RestartButton.h"

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
    //MusicButton musicButton;

    //Music musicMenuTheme;
    //Music musicFightTheme;
};