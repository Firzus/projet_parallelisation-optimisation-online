#include "WaitingScreen.h"

WaitingScreen::WaitingScreen(RenderWindow& window) : window(window)
{
	fontBold.loadFromFile("assets/fonts/Roboto-Bold.ttf");

    rectBackground.setSize(Vector2f(500, 500));
    rectBackground.setFillColor(Color(0, 0, 0, 204));

    rectContainerText.setSize(Vector2f(400, 100));
    rectContainerText.setFillColor(Color(133, 94, 194));
    rectContainerText.setPosition(Vector2f(50, 200));

    textConnection.setFont(fontBold);
    textConnection.setString("WAITING CONNEXION");
    textConnection.setCharacterSize(20);
    textConnection.setFillColor(Color(254, 254, 223));
    textConnection.setPosition(Vector2f(150, 239));
}

WaitingScreen::~WaitingScreen() {}

void WaitingScreen::Draw()
{
    window.draw(rectBackground);
    window.draw(rectContainerText);
    window.draw(textConnection);
}