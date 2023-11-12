#include "Application.h"

Application::Application() : window(VideoMode(500, 500), "Online Tic Tac Toe"), menu(window), game(window), result(window), state(ApplicationState::Menu)
{
    background.setSize(Vector2f(500, 500));
    background.setFillColor(Color(243, 197, 255));
}

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
            game.HandleInput(event);
        }
    }
}

void Application::Render()
{
    window.clear();
    window.draw(background);
    if (state == ApplicationState::Menu) {
        menu.Draw();
    }
    else if (state == ApplicationState::Game) {
        game.Draw();
    }
    window.display();
}

void Application::Update(float deltaTime)
{
    // Utilisez deltaTime pour ajuster les mouvements ou les animations
   // Exemple : position += vitesse * deltaTime;
}