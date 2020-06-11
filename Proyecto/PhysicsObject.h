#ifndef PhysicsObject_h
#define PhysicsObject_h
#include "RenderableObject.h"
#include "box2d/box2d.h"
#include <string>

enum BodyType{
    DYNAMIC,
    STATIC,
    KINEMATIC
};


class PhysicsObject: public RenderableObject{
public:
    PhysicsObject(App* ap, int posx, int posy, int w, int h, std::string image, BodyType type, float scaleX, float scaleY, int offsetX, int offsetY, bool debugRender);
    virtual ~PhysicsObject();
    virtual void update() override;
    virtual void render() override;
    virtual void handleInput(SDL_Event& event) override;
protected:
    b2Body* body;
    b2BodyDef bodyDef;
    b2PolygonShape shape;
    b2FixtureDef fixtureDef;
    SDL_Texture* colTexture;
    b2Vec2 scale;
    b2Vec2 offset;
    bool renderCollision;
};
#endif