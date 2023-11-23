#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <string>

using namespace std;

enum class ApplicationState {
    Menu,
    Game,
    Result
};

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

    void SetApplicationState(const ApplicationState& newState);
    ApplicationState GetApplicationState() const;

private:
    GameManager() : state(ApplicationState::Menu) {};
    
    ApplicationState state;

    string playerName;
    string winnerName;

    bool isConnected = false;
};

#endif // GAMEMANAGER_H