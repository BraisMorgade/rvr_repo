#ifndef Fighter_h
#define Fighterh
#include "PhysicsObject.h"

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
    Fighter(App* ap, int posx, int posy, int w, int h, std::string image, BodyType type);
    ~Fighter();
    virtual void update()override;
    virtual void handleInput(SDL_Event& event) override;
private:
    Inputs in;
    JumpState jumpState;
    float jumpSpeed;
};


#endif