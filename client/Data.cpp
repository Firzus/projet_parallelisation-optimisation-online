#include "Data.h"
#include "GameManager.h"
#include "Game.h"

Game game;

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
	currentPlayer = game.GetCurrentPlayer();
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
	isGameOver = game.IsGameOver();
}

bool Data::GetGameOver()
{
	return isGameOver;
}

void Data::SetPlayer1Score()
{
	scoreP1 = game.GetPlayer1Score();
}

int Data::GetPlayer1Score()
{
	return scoreP1;
}

void Data::SetPlayer2Score()
{
	scoreP2 = game.GetPlayer2Score();
}

int Data::GetPlayer2Score()
{
	return scoreP2;
}
