#include "Application.h"

Application::Application() :
window(VideoMode(500, 500), "Online Tic Tac Toe"),
menu(window),
game(window),
result(window),
exitButton(window),
restartButton(window),
state(ApplicationState::Menu)
{}

Application::~Application() {}

void Application::Run()
{
    Time deltaTime = clock.restart();

    while (window.isOpen()) {
        ProcessEvents();
        Update(deltaTime.asSeconds());
        Render();
    }
}

void Application::ProcessEvents()
{
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed)
        {
            window.close();
        }

        exitButton.HandleEvent(event);

        if (state == ApplicationState::Menu)
        {
            menu.HandleInput(event);
            if (menu.IsStartClicked())
            {
                state = ApplicationState::Game;
            }
        }
        else if (state == ApplicationState::Game)
        {
            if (event.type == Event::MouseButtonPressed) {
                game.HandleMouseClick(event.mouseButton.x, event.mouseButton.y);
            }
        }
        else if (state == ApplicationState::Result)
        {
            result.HandleInput(event);

            if (restartButton.HandleEvent(event)) {
                state = ApplicationState::Menu;
            }
        }
    }
}

void Application::Render()
{
    window.clear(Color(243, 197, 255));
    exitButton.Draw();

    if (state == ApplicationState::Menu) {
        menu.Draw();
    }
    else if (state == ApplicationState::Game) {
        game.Draw();
    }
    else if (state == ApplicationState::Result) {
        result.Draw();
        restartButton.Draw();
    }
    window.display();
}

void Application::Update(float deltaTime)
{
    game.Update();
}