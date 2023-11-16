#include <SFML/Graphics.hpp>

using namespace sf;

class Grid
{
public:
	Grid(RenderWindow& window);
	~Grid();

	void Draw();

private:
	RenderWindow& window;

	RectangleShape horizontalLine1, horizontalLine2, verticalLine1, verticalLine2;

	const float lineThickness = 4.0f;
	const float lineLength = 300.0f;
};