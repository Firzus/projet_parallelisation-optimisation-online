#include "Result.h"

Result::Result(RenderWindow& window) : window(window)
{
    isRestartButtonClicked = false;

	textureRestartButton.loadFromFile("assets/icons/restart.png");
	spriteRestartButton.setTexture(textureRestartButton);
	spriteRestartButton.setPosition(Vector2f(230, 296));

	fontBold.loadFromFile("assets/fonts/Roboto-Bold.ttf");

    textWhoWin.setFont(fontBold);
    textWhoWin.setCharacterSize(24);
    textWhoWin.setFillColor(Color(133, 94, 194));
}

Result::~Result() {}

void Result::Draw()
{
    window.draw(spriteRestartButton);
    window.draw(textWhoWin);
}

void Result::Update()
{
    textWhoWin.setString(GameManager::GetInstance().GetWinner() + " gagne");

    FloatRect textRect = textWhoWin.getGlobalBounds();
    textWhoWin.setPosition(Vector2f(500 / 2 - textRect.width / 2, 236));
}

void Result::HandleInput(Event& event)
{
    if (event.mouseButton.button == Mouse::Left) {
        Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
        if (spriteRestartButton.getGlobalBounds().contains(mousePos)) {
            isRestartButtonClicked = true;
        }
    }
}

bool Result::IsRestartButtonClicked() 
{
    return isRestartButtonClicked;
}