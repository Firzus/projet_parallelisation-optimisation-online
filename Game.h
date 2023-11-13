#include <SFML/Graphics.hpp>
#include <array>

#include "Grid.h"

// test
#include <iostream>

using namespace sf;
using namespace std;

class Game
{
public:
	Game(RenderWindow& window);
	~Game();

	void Draw();
	void HandleMouseClick(float x, float y);
	bool CheckWin(char playerSymbol);
	bool CheckDraw();
	void CleanBoard();
	Vector2f GetCellPosition(int row, int col);

private:
	RenderWindow& window;
	Grid grid;

	array<array<char, 3>, 3> board{};
	Texture textureX, textureO;
	Sprite spriteX, spriteO;
	bool playerHasWon;
	char currentPlayer;
	const int screenSize = 500;
	const int gridWidth = 300;
	const int gridSize = 3;
	const int offsetTexture = 18;
	const float cellSize = gridWidth / gridSize;
	const float xOffset = (screenSize - gridWidth) / 2 + offsetTexture;
	const float yOffset = (screenSize - gridWidth) / 2 + offsetTexture;
};