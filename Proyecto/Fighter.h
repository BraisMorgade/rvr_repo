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

enum MovState{
    STILL,
    WALKING_FORWARD,
    WALKING_BACKWARDS
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
    MovState movementState;
    AnimationMachine* animationMachine;
    float jumpSpeed;

    void handleJumpState();
    void handleMovementState();

    void jumpStart();
    void fallStart();
    void walkForwardStart();
    void walkBackwardsStart();
    void idleStart();
};


#endif