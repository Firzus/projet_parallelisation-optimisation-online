#include "Data.h"
#include "GameManager.h"
#include "Game.h"

void Data::SetPlayerName()
{
	playerName = GameManager::GetInstance().GetPlayerName();
}

std::string Data::GetPlayerName()
{
	return playerName;
}

void Data::SetCurrentToken()
{
	Game myGame;
	currentPlayer = myGame.GetCurrentPlayer();
}

char Data::GetCurrentToken()
{
	return currentPlayer;
}

void Data::SetWinner()
{
	winnerName = GameManager::GetInstance().GetWinner();
}

std::string Data::GetWinner()
{
	return winnerName;
}

void Data::SetBoard(const std::array<std::array<char, 3>, 3>& board)
{
	boardData = board;
}

void Data::SetConnection()
{
	isConnected = GameManager::GetInstance().GetStateConnection();
}

bool Data::GetConnection()
{
	return isConnected;
}

void Data::SetGameOver()
{
	Game myGame;
	isGameOver = myGame.IsGameOver();
}

bool Data::GetGameOver()
{
	return isGameOver;
}
