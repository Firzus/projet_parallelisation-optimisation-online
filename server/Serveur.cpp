#include "Serveur.h"

Serveur::Serveur() : window(VideoMode(500, 500), "Online Tic Tac Toe")
{

}

Serveur::~Serveur() {}

void Serveur::Run()
{
    Time deltaTime = clock.restart();

    while (window.isOpen()) {
        ProcessEvents();
        Update(deltaTime.asSeconds());
        Render();
    }
}

void Serveur::ProcessEvents()
{
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed)
        {
            window.close();
        }
    }
}

void Serveur::Render()
{
    window.clear();

 /*   sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    window.draw(shape);*/

    window.display();
}

void Serveur::Update(float deltaTime)
{
}
