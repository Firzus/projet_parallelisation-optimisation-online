#include "Application.h"
static clientConfig client;

Application::Application() :
	window(VideoMode(500, 500), "Online Tic Tac Toe"),
	menu(window),
	game(window),
	result(window),
	exitButton(window),
	networkButton(window),
	waitingScreen(window) {}

Application::~Application() {}

void Application::InitClient()
{
	client.Init(hWnd);
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

LRESULT CALLBACK Application::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_USER:
		client.HandleSocketMessage(wParam, lParam);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
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

		// Bloque les actions si pas de connexion
		if (GameManager::GetInstance().GetStateConnection())
		{
			exitButton.HandleEvent(event);

			if (GameManager::GetInstance().GetApplicationState() == ApplicationState::Menu)
			{
				menu.HandleInput(event);

				if (menu.IsStartClicked())
				{
					GameManager::GetInstance().SetApplicationState(ApplicationState::Game);
				}
			}
			else if (GameManager::GetInstance().GetApplicationState() == ApplicationState::Game)
			{
				if (event.type == Event::MouseButtonPressed) {
					game.HandleMouseClick(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));
				}

                if (game.IsGameOver())
                {
                    GameManager::GetInstance().SetApplicationState(ApplicationState::Result);
                }
            }
        }
    }
}

void Application::Render()
{
	window.clear(Color(243, 197, 255));
	exitButton.Draw();
	networkButton.Draw();

	if (GameManager::GetInstance().GetApplicationState() == ApplicationState::Menu) {
		menu.Draw();
	}
	else if (GameManager::GetInstance().GetApplicationState() == ApplicationState::Game) {
		game.Draw();
	}
	else if (GameManager::GetInstance().GetApplicationState() == ApplicationState::Result) {
		result.Draw();
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
}