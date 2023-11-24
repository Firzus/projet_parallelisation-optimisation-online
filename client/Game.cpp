#include "Game.h"
#include "clientConfig.h"
#include "Data.h"

clientConfig client;
Data da;

Game::Game() :
window(window),
grid(window),
scoreIndicator(window),
turnMessage(window)
{
}

Game::Game(RenderWindow& window) :
window(window),
grid(window),
scoreIndicator(window),
turnMessage(window)
{
	textureO.loadFromFile("assets/icons/o.png");
	textureX.loadFromFile("assets/icons/x.png");

	spriteO.setTexture(textureO);
	spriteX.setTexture(textureX);

    isGameOver = false;
    playerHasWon = false;
    currentPlayer = 'O';
    scoreP1 = 0;
    scoreP2 = 0;

    CleanBoard();
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

            //da.SetBoard(board);
        }
    }
}

void Game::Update()
{
    turnMessage.Update(GetPlayerName(currentPlayer));
    scoreIndicator.Update(scoreP1, scoreP2);
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
                UpdateScore(currentPlayer);
                StartNewRound();
            }
            else if (CheckDraw()) {
                StartNewRound();
            }
            else {
                currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
                da.SetCurrentToken();
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
    if (winner == 'O') {
        scoreP1++;
    }
    else if (winner == 'X') {
        scoreP2++;
    }

    client.sendJson();
    client.ReceiveData();
}

void Game::StartNewRound() {
    if (scoreP1 >= 3 || scoreP2 >= 3) {
        isGameOver = true;
        GetWinner();
    }
    else {
        CleanBoard();
    }
}

bool Game::IsGameOver() const
{
    return isGameOver;
}

void Game::GetWinner() const {
    if (scoreP1 > scoreP2) {
        GameManager::GetInstance().SetWinner(GameManager::GetInstance().GetPlayerName());
    }
    else if (scoreP2 > scoreP1) {
        GameManager::GetInstance().SetWinner("Ordinateur");
    }
}

void Game::ResetGame() {
    playerHasWon = false;
    currentPlayer = 'O';

    if (isGameOver) {
        scoreP1 = 0;
        scoreP2 = 0;
        isGameOver = false;
    }
    
    CleanBoard();
}

Vector2f Game::GetCellPosition(int row, int col) {
    return Vector2f(static_cast<float>(offset + col * cellSize), static_cast<float>(offset + row * cellSize));
}

string Game::GetPlayerName(char currentPlayer) {
    if (currentPlayer == 'O') {
        return GameManager::GetInstance().GetPlayerName();
    }
    else {
        return "Ordinateur";
    }
}

int Game::GetPlayer1Score() const
{
    return scoreP1;
}

int Game::GetPlayer2Score() const
{
    return scoreP2;
}

void Game::CleanBoard() {
    for (auto& row : board) {
        row.fill(' ');
    }
}