#ifndef PhysicsObject_h
#define PhysicsObject_h
#include "RenderableObject.h"
#include "box2d/box2d.h"
#include <string>

class PhysicsObject: public RenderableObject{
public:
    PhysicsObject(App* ap, int posx, int posy, int w, int h, std::string image);
    ~PhysicsObject();
    virtual void update()override;
protected:
    b2Body* body;
    b2BodyDef bodyDef;
    b2PolygonShape dynamicBox;
    b2FixtureDef fixtureDef;
};
#endif