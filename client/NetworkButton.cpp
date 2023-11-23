#include "NetworkButton.h"

NetworkButton::NetworkButton(RenderWindow& window) : window(window)
{
	textureNetworkOnButton.loadFromFile("assets/icons/network_on.png");
	textureNetworkOffButton.loadFromFile("assets/icons/network_off.png");

	spriteNetworkOnButton.setTexture(textureNetworkOnButton);
	spriteNetworkOnButton.setPosition(Vector2f(16, 444));

	spriteNetworkOffButton.setTexture(textureNetworkOffButton);
	spriteNetworkOffButton.setPosition(Vector2f(16, 444));
}

NetworkButton::~NetworkButton() {}

void NetworkButton::Draw()
{
    if (currentSprite != nullptr) {
        window.draw(*currentSprite);
    }
}

void NetworkButton::Update()
{
    if (GameManager::GetInstance().GetStateConnection()) {
        currentSprite = &spriteNetworkOnButton;
    }
    else {
        currentSprite = &spriteNetworkOffButton;
    }
}