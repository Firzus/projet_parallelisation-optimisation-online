#include <SFML/Graphics.hpp>

#include "GameManager.h"
#include "clientConfig.h"

using namespace sf;

class ExitButton
{
public:
	ExitButton(RenderWindow& window);
	~ExitButton();

	void Draw();
	void HandleEvent(Event& event);

private:
	RenderWindow& window;

	clientConfig  client;

	Texture textureExitButton;
	Sprite spriteExitButton;
};