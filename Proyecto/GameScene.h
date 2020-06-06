#ifndef GameScene_h
#define GameScene_h
#include "GameState.h"

class GameScene: public GameState{
public:
    GameScene(App* ap);
    ~GameScene();
};
#endif