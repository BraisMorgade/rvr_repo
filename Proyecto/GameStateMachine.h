#ifndef GameStateMachine_h
#define GameStateMachine_h
#include <map>
class App;
class GameState;

class GameStateMachine{
public:
    GameStateMachine(App * ap);
    ~GameStateMachine();
    GameState* getCurrentState();
    void changeState(std::string state);
private:
    GameState* currentState;
    std::map<std::string, GameState*> states;
    App* app;
};
#endif