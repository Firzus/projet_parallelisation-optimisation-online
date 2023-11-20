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

std::string Data::GetWinner()
{
	return winnerName;
}
