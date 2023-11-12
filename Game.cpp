#include "Game.h"

Game::Game(RenderWindow& window) : window(window), grid(window)
{

}

Game::~Game() {}

void Game::Draw()
{
	grid.Draw();
}

void Game::HandleInput(Event& event)
{
}
