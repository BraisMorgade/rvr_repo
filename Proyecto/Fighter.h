#ifndef Fighter_h
#define Fighterh
#include "PhysicsObject.h"
#include "AnimationMachine.h"

struct Inputs{
    bool left;
    bool right;
    bool up;
    bool down;
};

enum JumpState{
    GROUNDED,
    RISING,
    APEX,
    FALLING
};


class Fighter: public PhysicsObject{
public:
    Fighter(App* ap, int posx, int posy, int w, int h, std::string image, BodyType type, float scaleX, float scaleY, int offsetX, int offsetY, bool debugRender);
    ~Fighter();
    virtual void update()override;
    virtual void handleInput(SDL_Event& event) override;
private:
    Inputs in;
    JumpState jumpState;
    AnimationMachine* animationMachine;
    float jumpSpeed;
};


#endif