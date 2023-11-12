#include <SFML/Graphics.hpp>

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

};
