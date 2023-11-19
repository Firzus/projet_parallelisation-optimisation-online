#include "Application.h"

Application::Application() :
window(VideoMode(500, 500), "Online Tic Tac Toe"),
menu(window),
game(window),
result(window),
exitButton(window),
restartButton(window),
networkButton(window),
waitingScreen(window),
state(ApplicationState::Menu)
{}

Application::~Application() {}

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
            client.Shutdown();
            window.close();
        }

        exitButton.HandleEvent(event, client);

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
                game.HandleMouseClick(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));
            }

            if (game.IsGameOver())
            {
                state = ApplicationState::Result;
            }
        }
        else if (state == ApplicationState::Result)
        {
            result.HandleInput(event);

            if (result.IsRestartButtonClicked())
            {
                state = ApplicationState::Menu;
            }
        }
    }
}

void Application::Render()
{
    window.clear(Color(243, 197, 255));
    exitButton.Draw();
    networkButton.Draw();

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

    if (!GameManager::GetInstance().GetStateConnection())
    {
        waitingScreen.Draw();
    }

    window.display();
}

void Application::Update()
{
    game.Update();
    result.Update();
    networkButton.Update();
    waitingScreen.Update();

    bool state = GameManager::GetInstance().GetStateConnection();
    //OutputDebugStringA(std::to_string(state ? 1 : 0).c_str());
}