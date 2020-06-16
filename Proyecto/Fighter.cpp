#include "Fighter.h"
#include "App.h"
#include "RayCast.h"
#include "GameObject.h"
#include "GameStateMachine.h"
#include <math.h>
#include <iostream>

Fighter::Fighter(App *ap, int posx, int posy, int w, int h, std::string image, BodyType type, float scaleX, float scaleY, int offsetX, int offsetY, bool debugRender)
    : PhysicsObject(ap, posx, posy, w, h, image, type, scaleX, scaleY, offsetX, offsetY, debugRender)
{
    in.left = false;
    in.right = false;
    in.up = false;
    in.down = false;
    state=FALLING;
    grounded=false;
    body->SetFixedRotation(true);

    clip = new SDL_Rect;
    clip->x = 0;
    clip->y = 0;
    clip->w = 64;
    clip->h = 64;

    animationMachine = new AnimationMachine(16, 16, clip);

    addAnimations();
}

void Fighter::update()
{
    PhysicsObject::update();
    animationMachine->updateAnimation();
    playerControl();
    updateState();
    groundRayCast();
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
        case SDLK_ESCAPE:
            if(event.type==SDL_KEYDOWN)
                app->getStateMachine()->changeState("menu");
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

void Fighter::playerControl()
{
    switch (state)
    {
    case STILL:
    case WALKING_BACKWARDS:
    case WALKING_FORWARD:
        if (in.up)
        {
            body->SetLinearVelocity(b2Vec2(0, -5));
            if (in.right)
            {
                body->SetLinearVelocity(b2Vec2(1, -5));
            }
            else if (in.left)
            {
                body->SetLinearVelocity(b2Vec2(-1, -5));
            }
            jumpStart();
        }
        else if (in.atk)
        {
            body->SetLinearVelocity(b2Vec2(0, -5));
        }
        else if (in.right)
        {
            body->SetLinearVelocity(b2Vec2(1, body->GetLinearVelocity().y));
        }
        else if (in.left)
        {
            body->SetLinearVelocity(b2Vec2(-1, body->GetLinearVelocity().y));
        }
        else
            body->SetLinearVelocity(b2Vec2(0,body->GetLinearVelocity().y));
        
        break;
    case APEX:
    case FALLING:
        if (in.atk)
        {
            body->SetLinearVelocity(b2Vec2(0, -5));
        }
        break;
    default:
        break;
    }
}

void Fighter::updateState()
{
    switch (state)
    {
    case STILL:
        if (!grounded)
        {
            fallStart();
        }
        else if (body->GetLinearVelocity().x > 0.05)
        {
            walkForwardStart();
        }
        else if (body->GetLinearVelocity().x < -0.05)
        {
            walkBackwardsStart();
        }
        break;
    case WALKING_FORWARD:
        if (!grounded)
        {
            fallStart();
        }
        else if (grounded && abs(body->GetLinearVelocity().x) < 0.05)
        {
            idleStart();
        }
        else if (body->GetLinearVelocity().x < -0.05)
        {
            walkBackwardsStart();
        }
        break;
    case WALKING_BACKWARDS:
        if (!grounded)
        {
            fallStart();
        }
        else if (grounded&& abs(body->GetLinearVelocity().x) < 0.05)
        {
            idleStart();
        }
        else if (body->GetLinearVelocity().x > 0.05)
        {
            walkForwardStart();
        }
        break;
    case RISING:
        if (abs(body->GetLinearVelocity().y) < 0.05)
        {
            state = APEX;
        }
        break;
    case APEX:
        if (body->GetLinearVelocity().y > 0.05)
        {
            fallStart();
        }
        break;
    case FALLING:
        if (grounded)
        {
            idleStart();
        }
        break;
    default:
        break;
    }
}

void Fighter::groundRayCast(){
    RayCast callback;
    b2Vec2 p1;
    p1.x=body->GetPosition().x;
    p1.y=body->GetPosition().y;
    b2Vec2 p2;
    p2.x=body->GetPosition().x,
    p2.y=body->GetPosition().y+getBodyHeight()/2.0f + 0.05;

    app->getWorld()->RayCast(&callback, p1, p2);
    grounded=false;
    if(callback.m_fixture){
        GameObject* object=static_cast<GameObject*>(callback.m_fixture->GetBody()->GetUserData());
        if(object->getTag()=="Ground")
            grounded=true;
    }
}
/*
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
*/

void Fighter::jumpStart()
{
    state = RISING;
    animationMachine->playAnimation("jump");
}

void Fighter::fallStart()
{
    state = FALLING;
    animationMachine->playAnimation("fall");
}

void Fighter::walkForwardStart()
{
    flip = SDL_FLIP_NONE;
    flipBody(true);
    state = WALKING_FORWARD;
    animationMachine->playAnimation("walkForward");
}

void Fighter::walkBackwardsStart()
{
    flip = SDL_FLIP_HORIZONTAL;
    flipBody(false);
    state = WALKING_BACKWARDS;
    animationMachine->playAnimation("walkBackwards");
}

void Fighter::idleStart()
{
    state = STILL;
    animationMachine->playAnimation("idle");
}

void Fighter::addAnimations()
{

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

    info.beginningX = 6;
    info.beginningY = 4;
    info.loop = false;
    info.nframes = 6;
    info.animTime = 0.5f;
    info.direction = 1;
    animationMachine->addAnimation("groundAttack", info);
}