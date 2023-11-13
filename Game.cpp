#include "Game.h"

Game::Game(RenderWindow& window) : 
window(window),
grid(window)
{
	textureX.loadFromFile("assets/icons/x.png");
	textureO.loadFromFile("assets/icons/o.png");

	spriteX.setTexture(textureX);
	spriteO.setTexture(textureO);

    CleanBoard();
}

Game::~Game() {}

void Game::Draw()
{
	grid.Draw();

    for (int row = 0; row < gridSize; ++row) {
        for (int col = 0; col < gridSize; ++col) {
            Vector2f pos = GetCellPosition(row, col);

            if (board[row][col] == 'X') {
                spriteX.setPosition(pos);
                window.draw(spriteX);
            }
            else if (board[row][col] == 'O') {
                spriteO.setPosition(pos);
                window.draw(spriteO);
            }
        }
    }
}

void Game::HandleMouseClick(float x, float y) {
    x -= xOffset;
    y -= yOffset;

    if (x >= 0 && x < gridWidth && y >= 0 && y < gridWidth) {
        int col = static_cast<int>(x / cellSize);
        int row = static_cast<int>(y / cellSize);

        if (board[row][col] == ' ') {
            board[row][col] = currentPlayer;

            if (CheckWin(currentPlayer)) {
                cout << "le joueur : " << currentPlayer << " a gagne !" << endl;
            }
            else if (CheckDraw()) {
                cout << "Personne n'a gagne" << endl;
            }
            else {
                currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
            }
        }
    }
}

bool Game::CheckWin(char playerSymbol) {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == playerSymbol && board[i][1] == playerSymbol && board[i][2] == playerSymbol) {
            return true;
        }
    }

    for (int i = 0; i < 3; i++) {
        if (board[0][i] == playerSymbol && board[1][i] == playerSymbol && board[2][i] == playerSymbol) {
            return true;
        }
    }

    if (board[0][0] == playerSymbol && board[1][1] == playerSymbol && board[2][2] == playerSymbol) {
        return true;
    }

    if (board[0][2] == playerSymbol && board[1][1] == playerSymbol && board[2][0] == playerSymbol) {
        return true;
    }

    return false;
}

bool Game::CheckDraw() {
    for (auto& row : board) {
        for (char cell : row) {
            if (cell == ' ') {
                return false;
            }
        }
    }
    return true;
}

Vector2f Game::GetCellPosition(int row, int col) {
    return Vector2f(xOffset + col * cellSize, yOffset + row * cellSize);
}

void Game::CleanBoard() {
    for (auto& row : board) {
        row.fill(' ');
    }
    playerHasWon = false;
    currentPlayer = 'X';
}