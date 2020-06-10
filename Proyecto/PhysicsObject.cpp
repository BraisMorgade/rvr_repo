#include "PhysicsObject.h"
#include "App.h"
#include "box2d/b2_world.h"
#include "GameStateMachine.h"
#include <math.h>
#define _USE_MATH_DEFINES

PhysicsObject::PhysicsObject(App *ap, int posx, int posy, int w, int h, std::string image, BodyType type) : RenderableObject(ap, posx, posy, w, h, image)
{
    switch (type)
    {
    case DYNAMIC:
        bodyDef.type = b2_dynamicBody;
        break;
    case KINEMATIC:
        bodyDef.type = b2_kinematicBody;
        break;
    case STATIC:
        bodyDef.type = b2_staticBody;
        break;
    default:
        break;
    }
    bodyDef.position.Set((float)posX / 100.0f, (float)posY / 100.0f);
    body = app->getWorld()->CreateBody(&bodyDef);
    shape.SetAsBox((float)w / 100.0f / 2.0f, (float)h / 100.0f / 2.0f);
    fixtureDef.shape = &shape;
    if (type == DYNAMIC)
    {
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.3f;
    }
    body->CreateFixture(&fixtureDef);
}

void PhysicsObject::update()
{

    b2Vec2 position = body->GetPosition();
    posX = position.x * 100;
    posY = position.y * 100;
    ang = body->GetAngle()*180.0/M_PI;
}

void PhysicsObject::handleInput(SDL_Event &event)
{

    if (event.type == SDL_KEYDOWN)
    {
        if (event.key.keysym.sym == SDLK_ESCAPE)
        {
            app->getStateMachine()->changeState("menu");
        }
    }
}

PhysicsObject::~PhysicsObject()
{
    app->getWorld()->DestroyBody(body);
    body = nullptr;
}