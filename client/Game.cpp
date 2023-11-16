#include "Game.h"

Game::Game(RenderWindow& window) : 
window(window),
grid(window),
scoreIndicator(window),
turnMessage(window)
{
	textureX.loadFromFile("assets/icons/x.png");
	textureO.loadFromFile("assets/icons/o.png");

	spriteX.setTexture(textureX);
	spriteO.setTexture(textureO);

    ResetGame();
}

Game::~Game() {}

void Game::Draw()
{
	grid.Draw();
    turnMessage.Draw();
    scoreIndicator.Draw();

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

    cout << "Score - Joueur: " << scoreP1 << ", Ordinateur: " << scoreP2<< endl;
    cout << "Manche : " << currentRound << " sur 3" << endl;
}

void Game::Update()
{
    turnMessage.Update(GetPlayerName(currentPlayer));
}

void Game::HandleMouseClick(float x, float y) {
    x -= offset;
    y -= offset;

    if (x >= 0 && x < gridWidth && y >= 0 && y < gridWidth) {
        int col = static_cast<int>(x / cellSize);
        int row = static_cast<int>(y / cellSize);

        if (board[row][col] == ' ') {
            board[row][col] = currentPlayer;

            if (CheckWin(currentPlayer)) {
                cout << "le joueur : " << currentPlayer << " a gagne !" << endl;
                CleanBoard();
            }
            else if (CheckDraw()) {
                cout << "Personne n'a gagne" << endl;
                CleanBoard();
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

void Game::UpdateScore(char winner) {
    if (winner == 'X') {
        scoreP1++;
    }
    else if (winner == 'O') {
        scoreP2++;
    }
}

void Game::StartNewRound() {
    currentRound++;
    if (currentRound > 3) {
        DetermineFinalWinner();
    }
    else {
        CleanBoard();
    }
}

void Game::DetermineFinalWinner() {
    if (scoreP1 > scoreP2) {
        cout << "Le joueur remporte la victoire finale !" << endl;
    }
    else if (scoreP2 > scoreP1) {
        cout << "L'ordinateur remporte la victoire finale !" << endl;
    }
    else {
        cout << "La partie se termine par une égalité !" << endl;
    }

    ResetGame();
}

void Game::ResetGame() {
    playerHasWon = false;
    currentPlayer = 'X';
    scoreP1 = 0;
    scoreP2 = 0;
    currentRound = 1;

    CleanBoard();
}

Vector2f Game::GetCellPosition(int row, int col) {
    return Vector2f(offset + col * cellSize, offset + row * cellSize);
}

string Game::GetPlayerName(char currentPlayer) {
    if (currentPlayer == 'X') {
        return "Player";
    }
    else {
        return "Ordinateur";
    }
}

void Game::CleanBoard() {
    for (auto& row : board) {
        row.fill(' ');
    }
}