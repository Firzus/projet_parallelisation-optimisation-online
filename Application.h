#pragma once
#include <iostream>

#include <SFML/Graphics.hpp>

#include "Menu.h"
#include "Game.h"
#include "Result.h"

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
    virtual void Update(float deltaTime);

    RenderWindow window;
    ApplicationState state;
    RectangleShape background;
    Clock clock;
    Menu menu;
    Game game;
    Result result;
};