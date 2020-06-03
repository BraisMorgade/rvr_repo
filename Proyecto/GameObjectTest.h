#ifndef GameObjectTest_h
#define GameObjectTest_h
#include "GameObject.h"

class GameObjectTest : public GameObject{
public:
    GameObjectTest(SDL_Renderer* rd, int posx, int posy, int w, int h);
    ~GameObjectTest(){};
    virtual void start() override{};
    virtual void update() override{};
    virtual void render() override;
    virtual void handleInput(SDL_Event& event) override{};
private:
    SDL_Renderer* rend;
    SDL_Texture* texture;
    int posX, posY;
    int height, width;
};
#endif
