#ifndef HitDetectionBox_h
#define HitDetectionBox_h
#include "PhysicsObject.h"

class Fighter;

enum BoxType{
    HITBOX,
    HURTBOX
};

class HitDetectionBox: public PhysicsObject{
public:
    HitDetectionBox(App* ap, int posx, int posy,
    int w, int h, float scaleX, float scaleY,
    int offsetX, int offsetY, bool debugRender, 
    BoxType bType, Fighter* fighter);

    virtual void OnCollisionEnter(PhysicsObject* other) override;
    virtual void OnCollisionExit(PhysicsObject* other) override;
    virtual ~HitDetectionBox(){};
private:
    BoxType boxType;
    Fighter* fg;
};

#endif