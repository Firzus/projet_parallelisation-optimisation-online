#include <SFML/Graphics.hpp>

#include "GameManager.h"

using namespace sf;

class Result
{
public:
	Result(RenderWindow& window);
	~Result();

	void Draw();
	void Update();

private:
	RenderWindow& window;

	Text textWhoWin;
	Text textLabel;
	Font fontBold;

	const float spacing = 12.f;
};