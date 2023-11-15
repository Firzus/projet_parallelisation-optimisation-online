#include "Application.h"

Application::Application() :
window(VideoMode(500, 500), "Online Tic Tac Toe"),
menu(window),
game(window),
result(window),
exitButton(window),
restartButton(window),
//musicButton(window),
state(ApplicationState::Menu)
{
    //musicMenuTheme.openFromFile("assets/musics/menu_theme.wav");
    //musicFightTheme.openFromFile("assets/musics/fight_theme.wav");

    //musicMenuTheme.setLoop(true);
    //musicFightTheme.setLoop(true);

    //musicMenuTheme.setVolume(30.f);
    //musicFightTheme.setVolume(30.f);
}

Application::~Application()
{
    //musicMenuTheme.stop();
    //musicFightTheme.stop();
}

void Application::Run()
{
    MSG msg;
    ZeroMemory(&msg, sizeof(MSG));

    while (window.isOpen()) {
        ProcessEvents();
        Update();
        Render();

        // Traitement des messages Windows
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                window.close();
            }
            else {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
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

        //musicButton.HandleEvent(event);
        exitButton.HandleEvent(event);

        if (state == ApplicationState::Menu)
        {
            //if (musicButton.IsMusicPlaying()) {
            //    if (musicMenuTheme.getStatus() != Music::Playing) {
            //        musicMenuTheme.play();
            //    }
            //}
            //else {
            //    if (musicMenuTheme.getStatus() == Music::Playing) {
            //        musicMenuTheme.stop();
            //    }
            //}

            menu.HandleInput(event);
            if (menu.IsStartClicked())
            {
                state = ApplicationState::Game;
                //musicMenuTheme.stop();
            }
        }
        else if (state == ApplicationState::Game)
        {
           /* if (musicButton.IsMusicPlaying()) {
                if (musicFightTheme.getStatus() != Music::Playing) {
                    musicFightTheme.play();
                }
            }
            else {
                if (musicFightTheme.getStatus() == Music::Playing) {
                    musicFightTheme.stop();
                }
            }*/

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
    //musicButton.Draw();
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

void Application::Update()
{
    game.Update();
}