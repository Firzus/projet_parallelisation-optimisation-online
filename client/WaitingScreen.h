#include <SFML/Graphics.hpp>

using namespace sf;

class WaitingScreen
{
public:
	WaitingScreen(RenderWindow& window);
	~WaitingScreen();

	void Draw();
	void Update();

private:
	RenderWindow& window;

	Font fontSemiBold;
	Text textConnection;

	RectangleShape rectBackground;
	RectangleShape rectContainerText;
};