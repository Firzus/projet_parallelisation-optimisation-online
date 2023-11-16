#include <iostream>

#include <SFML/Graphics.hpp>

#include "Menu.h"
#include "Game.h"
#include "Result.h"
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
    ExitButton exitButton;
    RestartButton restartButton;

    Clock clock;
};