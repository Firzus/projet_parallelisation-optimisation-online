#include "Result.h"

Result::Result(RenderWindow& window) : window(window)
{
	fontBold.loadFromFile("assets/fonts/Roboto-Bold.ttf");

    textWhoWin.setFont(fontBold);
    textWhoWin.setCharacterSize(24);

    textLabel.setFont(fontBold);
    textLabel.setFillColor(Color(133, 94, 194));
    textLabel.setCharacterSize(24);
    textLabel.setString("GAGNE");

    isGameRestarted = false;
}

Result::~Result() {}

void Result::Draw()
{
    window.draw(textWhoWin);
    window.draw(textLabel);
}

void Result::Update()
{
    if (GameManager::GetInstance().GetWinner() != "Ordinateur")
    {
        textWhoWin.setFillColor(Color(254, 254, 223));
    }
    else
    {
        textWhoWin.setFillColor(Color(0, 201, 168));
    }

    textWhoWin.setString(GameManager::GetInstance().GetWinner());

    FloatRect rectTextWhoWin = textWhoWin.getGlobalBounds();
    FloatRect rectTextLabel = textLabel.getGlobalBounds();

    textWhoWin.setPosition(Vector2f(250 - (rectTextWhoWin.width + rectTextLabel.width + spacing) / 2, 236));
    textLabel.setPosition(Vector2f(textWhoWin.getPosition().x + rectTextWhoWin.width + spacing, 236));
}