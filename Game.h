#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Game {
public:
    Game();
    virtual ~Game();

    void Run();

private:
    sf::RenderWindow window;
    sf::CircleShape shape;

    void ProcessEvents();
    void Render();
    virtual void Update();
};