#include "ExitButton.h"

ExitButton::ExitButton(RenderWindow& window) : window(window)
{
	textureExitButton.loadFromFile("assets/icons/exit.png");

	spriteExitButton.setTexture(textureExitButton);
	spriteExitButton.setPosition(Vector2f(444, 444));
}

ExitButton::~ExitButton() {}

void ExitButton::Draw()
{
	window.draw(spriteExitButton);
}

void ExitButton::HandleEvent(Event& event)
{
	if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
		if (spriteExitButton.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
			client.Shutdown();
			window.close();
		}
	}
}
