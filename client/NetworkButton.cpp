#include "NetworkButton.h"

NetworkButton::NetworkButton(RenderWindow& window) : window(window)
{
	textureNetworkOnButton.loadFromFile("assets/icons/network_on.png");
	textureNetworkOffButton.loadFromFile("assets/icons/network_off.png");

	spriteNetworkOnButton.setTexture(textureNetworkOnButton);
	spriteNetworkOnButton.setPosition(Vector2f(444, 444));

	spriteNetworkOffButton.setTexture(textureNetworkOffButton);
	spriteNetworkOffButton.setPosition(Vector2f(444, 444));
}

NetworkButton::~NetworkButton() {}

void NetworkButton::Draw()
{
	if (GameManager::GetInstance().GetStateConnection()) {
		window.draw(spriteNetworkOnButton);
	}
	else {
		window.draw(spriteNetworkOffButton);
	}
}

void NetworkButton::Update()
{

}