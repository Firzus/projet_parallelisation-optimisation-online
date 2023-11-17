#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <string>

using namespace std;

class GameManager {
public:
    static GameManager& GetInstance() {
        static GameManager instance;
        return instance;
    }

    GameManager(const GameManager&) = delete;
    GameManager& operator=(const GameManager&) = delete;

    void SetPlayerName(const string& name);
    string GetPlayerName() const;
   
    void SetWinner(const string& name);
    string GetWinner() const;

    void SetConnection(const bool& state);
    bool GetStateConnection() const;

private:
    GameManager() {}

    string playerName;
    string winnerName;

    bool isConnected = true;
};

#endif // GAMEMANAGER_H