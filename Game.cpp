#include "Game.h"

Game::Game() : window(sf::VideoMode(200, 200), "SFML works!"), shape(100.f)
{
	shape.setFillColor(sf::Color::Green);
}

Game::~Game() {}

void Game::Run()
{
    while (window.isOpen()) {
        ProcessEvents();
        Update();
        Render();
    }
}

void Game::ProcessEvents()
{
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void Game::Render() 
{
    window.clear();
    window.draw(shape);
    window.display();
}

void Game::Update()
{

}