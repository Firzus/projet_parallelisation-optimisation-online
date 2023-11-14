#include <SFML/Graphics.hpp>

using namespace sf;
 
class RestartButton
{
public:
	RestartButton(RenderWindow& window);
	~RestartButton();

	void Draw();
	bool HandleEvent(Event& event);

private:
	RenderWindow& window;

	Texture textureRestartButton;
	Sprite spriteRestartButton;
};
