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

string Data::GetWinner()
{
	return winnerName;
}

void Data::SetBoard(const array<array<char, 3>, 3>& board)
{
	boardData = board;
}

void Data::SetConnection()
{
	if (GameManager::GetInstance().GetStateConnection())
	{
		isConnected = 1;
	}
	else
	{
		isConnected = 0;
	}
}

int Data::GetConnection()
{
	return isConnected;
}

void Data::SetGameOver()
{
	Game myGame;

	if (myGame.IsGameOver())
	{
		isGameOver = 1;
	}
	else
	{
		isGameOver = 0;
	}
}

int Data::GetGameOver()
{
	return isGameOver;
}
