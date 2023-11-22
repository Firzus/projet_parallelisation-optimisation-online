#pragma once
#include "framework.h"
#include <stdio.h>
#include <iostream>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

class Data
{
public:
	void SetPlayerName();
	string GetPlayerName();

	void SetCurrentToken();
	char GetCurrentToken();

	void SetWinner();
	string GetWinner();

	void SetBoard(const std::array<std::array<char,3>, 3>& board);
	const std::array<std::array<char, 3>, 3>& GetBoard() const { return boardData;};
	json GetBoardAsJson() const;

	void SetConnection();
	int GetConnection();

	void SetGameOver();
	int GetGameOver();
private:

	int isGameOver;
	int isConnected;
	string playerName;
	string winnerName;
	char currentPlayer;
	
	array<array<char, 3>, 3> boardData;
};