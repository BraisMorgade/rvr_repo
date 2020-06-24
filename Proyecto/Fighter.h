#ifndef Fighter_h
#define Fighterh
#include "PhysicsObject.h"
#include "AnimationMachine.h"
#include "HitDetectionBox.h"

struct Inputs{
    bool left=false;
    bool right=false;
    bool up=false;
    bool down=false;
    bool atk=false;
};
enum MovementState{
    STILL,
    WALKING_FORWARD,
    WALKING_BACKWARDS,
    RISING,
    FALLING,
    ATK,
    J_ATK,
    FIREBALL,
    ANTI_AIR
};

class Fighter: public PhysicsObject{
public:
    Fighter(App* ap, int posx, int posy, int w, int h, std::string image, BodyType type, float scaleX, float scaleY, int offsetX, int offsetY, bool debugRender, bool localPlayer);
    ~Fighter();
    virtual void update()override;
    virtual void render()override;
    virtual void handleInput(SDL_Event& event) override;
    virtual void to_bin() override;
    virtual int from_bin(char* data) override;
private:
    Inputs in;
    MovementState state;
    AnimationMachine* animationMachine;
    HitDetectionBox* hitbox;
    HitDetectionBox* hurtbox;
    bool local;

    float jumpSpeed;
    bool grounded;
    void addAnimations();

    void playerControl();

    void updateState();

    void groundRayCast();

    void handleJumpState();
    void handleMovementState();

    void jumpStart();
    void fallStart();
    void walkForwardStart();
    void walkBackwardsStart();
    void idleStart();
};


#endif