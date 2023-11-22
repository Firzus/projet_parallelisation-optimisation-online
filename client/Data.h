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

	void SetPlayerToken();
	char GetPlayerToken();

	void SetWinner();
	string GetWinner();

	void SetBoard(const array<array<char,3>, 3>& board);
	const array<array<char, 3>, 3>& GetBoard() const { return boardData;};

	void SetAppState();
	string GetAppState();

	void SetBoard(const std::array<std::array<char,3>, 3>& board);
	const std::array<std::array<char, 3>, 3>& GetBoard() const { return boardData;};

	void SetConnection();
	bool GetConnection();

	void SetGameOver();
	bool GetGameOver();

private:
	bool isGameOver;
	bool isConnected;
	string playerName;
	string winnerName;
	char currentPlayer;
	string appState;
	
	array<array<char, 3>, 3> boardData;
};