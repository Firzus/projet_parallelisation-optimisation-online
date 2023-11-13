#include "TurnMessage.h"

TurnMessage::TurnMessage(RenderWindow& window) : window(window)
{
    fontBold.loadFromFile("assets/fonts/Roboto-Bold.ttf");

    textWhoPlay.setFont(fontBold);
    textWhoPlay.setCharacterSize(24);
    textWhoPlay.setFillColor(Color(133, 94, 194));

    FloatRect textRect = textWhoPlay.getGlobalBounds();
    textWhoPlay.setPosition(Vector2f(500 / 2 - textRect.width / 2, 456));
}

TurnMessage::~TurnMessage() {}

void TurnMessage::Draw()
{
    window.draw(textWhoPlay);
}

void TurnMessage::Update(const string& playerName)
{
    string message = "C'est à " + playerName + " de jouer";
    textWhoPlay.setString(message);

    FloatRect textRect = textWhoPlay.getGlobalBounds();
    textWhoPlay.setPosition(Vector2f(500 / 2 - textRect.width / 2, 456));
}