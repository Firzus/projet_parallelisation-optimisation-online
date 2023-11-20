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
	string GetPlayerName();

	void SetPlayerToken();
	char GetPlayerToken();

	void SetWinner();
	string GetWinner();


private:
	string playerName;
	string winnerName;
	char currentPlayer;
	
	array<array<char, 3>, 3> board{};
};