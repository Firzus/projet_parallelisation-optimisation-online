#include "Data.h"
#include "GameManager.h"
#include "Game.h"

void Data::SetPlayerName()
{
	playerName = GameManager::GetInstance().GetPlayerName();
}

string Data::GetPlayerName()
{
	return playerName;
}

void Data::SetPlayerToken()
{
	Game myGame;
	currentPlayer = myGame.GetCurrentPlayer();
}

char Data::GetPlayerToken()
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

void Data::GetGameOver()
{
	return isGameOver;
}
void Data::SetAppState()
{
	// void
}

string Data::GetAppState()
{
	switch (GameManager::GetInstance().GetApplicationState())
	{
	case ApplicationState::Menu:
		return "menu";
		break;
	case ApplicationState::Game:
		return "game";
		break;
	case ApplicationState::Result:
		return "result";
		break;
	default:
		break;
	}
}
