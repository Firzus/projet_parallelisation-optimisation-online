#pragma once
#include "framework.h"
#include <stdio.h>
#include <iostream>
#include "json.hpp"
using json = nlohmann::json;

class Data
{
public:
	void SetPlayerName();
	std::string GetPlayerName();

	void SetPlayerToken();
	char GetPlayerToken();

	void SetWinner();
	std::string GetWinner();

	void SetBoard(const std::array<std::array<char,3>, 3>& board);
	const std::array<std::array<char, 3>, 3>& GetBoard() const { return boardData;};
private:
	std::string playerName;
	std::string winnerName;
	char currentPlayer;
	
	std::array<std::array<char, 3>, 3> boardData;
};