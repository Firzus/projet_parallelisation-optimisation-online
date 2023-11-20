#include <SFML/Graphics.hpp>

using namespace sf;

class WaitingScreen
{
public:
	WaitingScreen(RenderWindow& window);
	~WaitingScreen();

	void Draw();

private:
	RenderWindow& window;

	Font fontBold;
	Text textConnection;

	RectangleShape rectBackground;
	RectangleShape rectContainerText;
};