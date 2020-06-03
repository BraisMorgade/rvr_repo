#ifndef GameStateTest_h
#define GameStateTest_h
#include <list>
#include "GameState.h"

class GameStateTest: public GameState{
public:
    GameStateTest(App* ap);
    ~GameStateTest();
    virtual void render(SDL_Renderer* render) override;
};
#endif