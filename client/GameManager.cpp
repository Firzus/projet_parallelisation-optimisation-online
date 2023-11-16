#include "GameManager.h"

void GameManager::SetPlayerName(const string& name) {
    playerName = name;
}

string GameManager::GetPlayerName() const {
    return playerName;
}

void GameManager::SetWinner(const string& name)
{
    winnerName = name;
}

string GameManager::GetWinner() const
{
    return winnerName;
}