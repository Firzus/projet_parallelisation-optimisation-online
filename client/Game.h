#include <SFML/Graphics.hpp>

#include <array>
#include <string>

#include "Grid.h"
#include "TurnMessage.h"
#include "ScoreIndicator.h"

#include "GameManager.h"

using namespace sf;

class Game
{
public:
	Game();
	Game(RenderWindow& window);
	~Game();

	void Draw();
	void Update();
	void HandleMouseClick(float x, float y);
	bool CheckWin(char playerSymbol);
	bool CheckDraw();
	void CleanBoard();
	void UpdateScore(char winner);
	void StartNewRound();
	Vector2f GetCellPosition(int row, int col);
	string GetPlayerName(char currentPlayer);
	char GetCurrentPlayer() { return currentPlayer; }
	bool IsGameOver();
	void GetWinner();

	void ResetGame();

private:

	RenderWindow& window;

	Grid grid;
	TurnMessage turnMessage;
	ScoreIndicator scoreIndicator;

	Texture textureX, textureO;
	Sprite spriteX, spriteO;

	array<array<char, 3>, 3> board{};

	bool playerHasWon;
	bool isGameOver;
	char currentPlayer;
	const int screenSize = 500;
	const int gridWidth = 300;
	const int gridSize = 3;
	const int cellSize = 100;
	const int offset = 118;
	int scoreP1;
	int scoreP2;
};