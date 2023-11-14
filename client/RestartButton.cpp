#include "RestartButton.h"

RestartButton::RestartButton(RenderWindow& window) : window(window)
{
	textureRestartButton.loadFromFile("assets/icons/restart.png");

	spriteRestartButton.setTexture(textureRestartButton);
	spriteRestartButton.setPosition(Vector2f(230, 296));
}

RestartButton::~RestartButton() {}

void RestartButton::Draw()
{
	window.draw(spriteRestartButton);
}

bool RestartButton::HandleEvent(Event& event)
{
	if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
		if (spriteRestartButton.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
			return true;
		}
	}
	return false;
}
