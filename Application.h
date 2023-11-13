#include <iostream>

#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>

#include "Menu.h"
#include "Game.h"
#include "Result.h"
#include "MusicButton.h"
#include "ExitButton.h"
#include "RestartButton.h"

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
    void Update(float deltaTime);

    RenderWindow window;
    ApplicationState state;

    Menu menu;
    Game game;
    Result result;

    //MusicButton musicButton;
    ExitButton exitButton;
    RestartButton restartButton;

    Clock clock;
    //Music musicMenuTheme;
    //Music musicFightTheme;
};