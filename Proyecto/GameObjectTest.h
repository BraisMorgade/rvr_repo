#ifndef GameObjectTest_h
#define GameObjectTest_h
#include "GameObject.h"
#include "box2d/box2d.h"

class App;

class GameObjectTest : public GameObject{
public:
    GameObjectTest(App* ap, int posx, int posy, int w, int h);
    ~GameObjectTest(){};
    virtual void start() override{};
    virtual void update() override;
    virtual void render() override;
    virtual void handleInput(SDL_Event& event) override{};
protected:
    App* app;
    int posX, posY;
    int height, width;
    b2Body* body;
    b2BodyDef bodyDef;
    b2PolygonShape dynamicBox;
    b2FixtureDef fixtureDef;
    SDL_Texture* texture;
};
#endif
