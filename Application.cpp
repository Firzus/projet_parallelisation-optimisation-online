#include "Application.h"

Application::Application() :
window(VideoMode(500, 500), "Online Tic Tac Toe"),
menu(window),
game(window),
result(window),
musicButton(window),
exitButton(window),
state(ApplicationState::Menu)
{
    background.setSize(Vector2f(500, 500));
    background.setFillColor(Color(243, 197, 255));

    musicMenuTheme.openFromFile("assets/musics/menu_theme.wav");
    musicFightTheme.openFromFile("assets/musics/fight_theme.wav");
    musicMenuTheme.setLoop(true);
    musicFightTheme.setLoop(true);
    musicMenuTheme.setVolume(30.f);
    musicFightTheme.setVolume(30.f);
}

Application::~Application()
{
    musicMenuTheme.stop();
    musicFightTheme.stop();
}

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

        musicButton.HandleEvent(event);
        exitButton.HandleEvent(event);

        if (state == ApplicationState::Menu)
        {
            if (musicButton.IsMusicPlaying()) {
                if (musicMenuTheme.getStatus() != Music::Playing) {
                    musicMenuTheme.play();
                }
            }
            else {
                if (musicMenuTheme.getStatus() == Music::Playing) {
                    musicMenuTheme.stop();
                }
            }

            menu.HandleInput(event);
            if (menu.IsStartClicked())
            {
                state = ApplicationState::Game;
                musicMenuTheme.stop();
            }
        }
        else if (state == ApplicationState::Game)
        {
            if (musicButton.IsMusicPlaying()) {
                if (musicFightTheme.getStatus() != Music::Playing) {
                    musicFightTheme.play();
                }
            }
            else {
                if (musicFightTheme.getStatus() == Music::Playing) {
                    musicFightTheme.stop();
                }
            }

            game.HandleInput(event);
        }
        else if (state == ApplicationState::Result)
        {
            result.HandleInput(event);
        }
    }
}

void Application::Render()
{
    window.clear();
    window.draw(background);
    musicButton.Draw();
    exitButton.Draw();

    if (state == ApplicationState::Menu) {
        menu.Draw();
    }
    else if (state == ApplicationState::Game) {
        game.Draw();
    }
    else if (state == ApplicationState::Result) {
        result.Draw();
    }
    window.display();
}

void Application::Update(float deltaTime)
{

}