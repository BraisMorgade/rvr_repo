#pragma once
#include <map>

class GameState;

class GameStateMachine{
public:
    ~GameStateMachine();
    static GameStateMachine* getInstance();
    GameState* getCurrentState();
    void changeState(std::string state);
private:
    GameStateMachine();
    GameStateMachine(GameStateMachine &) = delete;
    GameStateMachine & operator=(const GameStateMachine &)=delete;
    GameState* currentState;
    std::map<std::string, GameState*> states;
    static GameStateMachine* instance;
};