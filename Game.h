#include <SFML/Graphics.hpp>

#include <sstream>
#include <array>
#include <string>

#include "Grid.h"
#include "TurnMessage.h"

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
	void Update();
	void HandleMouseClick(float x, float y);
	bool CheckWin(char playerSymbol);
	bool CheckDraw();
	void CleanBoard();
	Vector2f GetCellPosition(int row, int col);
	string GetPlayerName(char currentPlayer);

private:
	RenderWindow& window;
	Grid grid;
	TurnMessage turnMessage;

	Texture textureX, textureO;
	Sprite spriteX, spriteO;

	array<array<char, 3>, 3> board{};

	bool playerHasWon;
	char currentPlayer;
	const int screenSize = 500;
	const int gridWidth = 300;
	const int gridSize = 3;
	const int cellSize = 100;
	const int offset = 118;
};