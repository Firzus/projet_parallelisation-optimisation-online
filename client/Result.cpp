#include "Result.h"

Result::Result(RenderWindow& window) : window(window)
{         
	fontBold.loadFromFile("assets/fonts/Roboto-Bold.ttf");

    textWhoWin.setFont(fontBold);
    textWhoWin.setCharacterSize(24);
    textWhoWin.setFillColor(Color(133, 94, 194));

    isGameRestarted = false;
}

Result::~Result() {}

void Result::Draw()
{
    window.draw(textWhoWin);
}

void Result::Update()
{
    textWhoWin.setString(GameManager::GetInstance().GetWinner() + " gagne");

    FloatRect textRect = textWhoWin.getGlobalBounds();
    textWhoWin.setPosition(Vector2f(500 / 2 - textRect.width / 2, 236));
}