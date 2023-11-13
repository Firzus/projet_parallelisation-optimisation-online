#include <SFML/Graphics.hpp>

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

	Texture textureExitButton;
	Sprite spriteExitButton;
};