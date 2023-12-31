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
	string GetCurrentToken();

	void SetWinner();
	string GetWinner();

	void SetBoard(const array<array<char,3>, 3>& board);
	const array<array<char, 3>, 3>& GetBoard() const;
	json GetBoardAsJson() const;

	void SetConnection();
	bool GetConnection();

	void SetGameOver();
	bool GetGameOver();

private:
	bool isGameOver;
	bool isConnected;
	string playerName;
	string winnerName;
	string currentPlayer;
	
	array<array<char, 3>, 3> boardData;
};