#ifndef GameScene_h
#define GameScene_h
#include "GameState.h"
#include "Serializable.h"
#include "Socket.h"

class GameScene: public GameState{
public:
    GameScene(App* ap);
    ~GameScene();
    virtual void start() override;
    virtual void send() override;
    virtual void receive() override;

private:

    Serializable* localFg=nullptr;
    Serializable* remoteFg=nullptr;
    bool connected=false;

    Socket* remote=nullptr;
};
#endif