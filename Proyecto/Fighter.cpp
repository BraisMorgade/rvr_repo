#include "Fighter.h"
#include <math.h>

Fighter::Fighter(App *ap, int posx, int posy, int w, int h, std::string image, BodyType type, float scaleX, float scaleY, int offsetX, int offsetY, bool debugRender)
    : PhysicsObject(ap, posx, posy, w, h, image, type, scaleX, scaleY, offsetX, offsetY, debugRender)
{
    in.left = false;
    in.right = false;
    in.up = false;
    in.down = false;
    jumpState = FALLING;
    movementState=STILL;

    body->SetFixedRotation(true);

    clip = new SDL_Rect;
    clip->x = 0;
    clip->y = 0;
    clip->w = 64;
    clip->h = 64;

    animationMachine = new AnimationMachine(16, 16, clip);
    AnimInfo info;
    info.beginningX = 0;
    info.beginningY = 0;
    info.loop = true;
    info.nframes = 4;
    info.animTime = 1.0f;
    info.direction = 1;
    animationMachine->addAnimation("idle", info);
    animationMachine->playAnimation("idle");

    info.beginningX = 0;
    info.beginningY = 1;
    info.loop = true;
    info.nframes = 8;
    info.animTime = 1.0f;
    info.direction = 1;
    animationMachine->addAnimation("walkForward", info);

    info.beginningX = 0;
    info.beginningY = 1;
    info.loop = true;
    info.nframes = 8;
    info.animTime = 1.0f;
    info.direction = -1;
    animationMachine->addAnimation("walkBackwards", info);

    info.beginningX = 0;
    info.beginningY = 2;
    info.loop = false;
    info.nframes = 4;
    info.animTime = 0.5f;
    info.direction = 1;
    animationMachine->addAnimation("jump", info);

    info.beginningX = 4;
    info.beginningY = 2;
    info.loop = false;
    info.nframes = 4;
    info.animTime = 0.5f;
    info.direction = 1;
    animationMachine->addAnimation("fall", info);
}

void Fighter::update()
{
    PhysicsObject::update();
    animationMachine->updateAnimation();
    handleJumpState();
    if (jumpState == GROUNDED)
        handleMovementState();
}

void Fighter::handleInput(SDL_Event &event)
{
    if (event.type == SDL_KEYDOWN || SDL_KEYUP)
    {
        bool value = (event.type == SDL_KEYDOWN);
        switch (event.key.keysym.sym)
        {
        case SDLK_LEFT:
            in.left = value;
            break;
        case SDLK_RIGHT:
            in.right = value;
            break;
        case SDLK_DOWN:
            in.down = value;
            break;
        case SDLK_UP:
            in.up = value;
            break;
        default:
            break;
        }
    }
    //enviar Input al otro cliente
}

Fighter::~Fighter()
{
}

void Fighter::handleJumpState()
{
    switch (jumpState)
    {
    case GROUNDED:
        if (in.up)
        {
            if (in.right)
                body->SetLinearVelocity(b2Vec2(1, -5));
            else if (in.left)
                body->SetLinearVelocity(b2Vec2(-1, -5));
            else
                body->SetLinearVelocity(b2Vec2(0, -5));

            jumpStart();
        }
        else if (in.right)
            body->SetLinearVelocity(b2Vec2(1, body->GetLinearVelocity().y));
        else if (in.left)
            body->SetLinearVelocity(b2Vec2(-1, body->GetLinearVelocity().y));
        else
            body->SetLinearVelocity(b2Vec2(0, body->GetLinearVelocity().y));
        break;
    case FALLING:
        if (abs(body->GetLinearVelocity().y) <= 0.05)
            idleStart();
        break;
    case RISING:
        if (abs(body->GetLinearVelocity().y) <= 0.05)
            jumpState = APEX;
        break;
    case APEX:
        if (abs(body->GetLinearVelocity().y) > 0.05)
        {
            fallStart();
        }
        break;
    default:
        break;
    }
}

void Fighter::handleMovementState()
{
    switch (movementState)
    {
    case STILL:
        if (body->GetLinearVelocity().x > 0.05)
        {
            walkForwardStart();
        }
        else if (body->GetLinearVelocity().x < -0.05)
        {
            walkBackwardsStart();
        }
        break;
    case WALKING_BACKWARDS:
        if (body->GetLinearVelocity().x > 0.05)
        {
            walkForwardStart();
        }
        else if (abs(body->GetLinearVelocity().x) < 0.05)
        {
            idleStart();
        }
        break;
    case WALKING_FORWARD:
        if (body->GetLinearVelocity().x < -0.05)
        {
            walkBackwardsStart();
        }
        else if (abs(body->GetLinearVelocity().x) < 0.05)
        {
            idleStart();
        }
        break;
    default:
        break;
    }
}

void Fighter::jumpStart()
{
    jumpState = RISING;
    animationMachine->playAnimation("jump");
}

void Fighter::fallStart()
{
    jumpState = FALLING;
    animationMachine->playAnimation("fall");
}

void Fighter::walkForwardStart()
{
    jumpState = GROUNDED;
    movementState = WALKING_FORWARD;
    animationMachine->playAnimation("walkForward");
}

void Fighter::walkBackwardsStart()
{
    jumpState = GROUNDED;
    movementState = WALKING_BACKWARDS;
    animationMachine->playAnimation("walkBackwards");
}

void Fighter::idleStart()
{
    jumpState = GROUNDED;
    movementState = STILL;
    animationMachine->playAnimation("idle");
}