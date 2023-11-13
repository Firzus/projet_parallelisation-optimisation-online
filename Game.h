#include <SFML/Graphics.hpp>

#include <sstream>
#include <array>
#include <string>

#include "Grid.h"

// debug
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
	string GetPlayerName(char currentPlayer);
	void DisplayCurrentPlayer(char currentPlayer);

private:
	RenderWindow& window;
	Grid grid;

	Text textWhoPlay;
	Font fontBold;

	Texture textureX, textureO;
	Sprite spriteX, spriteO;

	array<array<char, 3>, 3> board{};

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