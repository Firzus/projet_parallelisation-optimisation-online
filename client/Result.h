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
	Font fontBold;

	bool isGameRestarted;
};