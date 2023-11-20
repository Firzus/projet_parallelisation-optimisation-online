#include <SFML/Graphics.hpp>

#include "GameManager.h"

using namespace sf;

class NetworkButton
{
public:
	NetworkButton(RenderWindow& window);
	~NetworkButton();

	void Draw();
	void Update();

private:
	RenderWindow& window;

	Texture textureNetworkOnButton, textureNetworkOffButton;
	Sprite spriteNetworkOnButton, spriteNetworkOffButton;
};

