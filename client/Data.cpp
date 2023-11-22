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

string Data::GetCurrentToken()
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
		string rowString;
		for (char c : row) {
			rowString += c;
		}
		boardJson.push_back(rowString);
	}

	return boardJson;
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
