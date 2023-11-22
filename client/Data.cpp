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

const array<array<char, 3>, 3>& Data::GetBoard() const
{
	return boardData;
}

json Data::GetBoardAsJson() const
{
	json boardJson;
	
	for (const auto& row : boardData) {
		std::string rowString;
		for (char c : row) {
			// Convertir le char en string et l'ajouter à la ligne
			rowString += c;
		}
		// Ajouter la ligne convertie en string au tableau JSON
		boardJson.push_back(rowString);
	}

	return boardJson;
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
