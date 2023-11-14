#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Result
{
public:
	Result(RenderWindow& window);
	~Result();

	void Draw();
	void HandleInput(Event& event);

private:

};