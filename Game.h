#include <SFML/Graphics.hpp>

#include "Grid.h"

using namespace sf;
using namespace std;

class Game
{
public:
	Game(RenderWindow& window);
	~Game();

	void Draw();
	void HandleInput(Event& event);

private:
	RenderWindow& window;
	Grid grid;
};
