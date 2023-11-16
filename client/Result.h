#include <SFML/Graphics.hpp>

#include "GameManager.h"

using namespace sf;
using namespace std;

class Result
{
public:
	Result(RenderWindow& window);
	~Result();

	void Draw();
	void Update();
	void HandleInput(Event& event);
	bool IsRestartButtonClicked();

private:
	RenderWindow& window;

	Text textWhoWin;
	Font fontBold;

	Texture textureRestartButton;
	Sprite spriteRestartButton;

	bool isRestartButtonClicked;
};