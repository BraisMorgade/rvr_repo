#include "PhysicsObject.h"
#include "App.h"
#include "box2d/b2_world.h"
#include "GameStateMachine.h"
#include <math.h>
#define _USE_MATH_DEFINES

PhysicsObject::PhysicsObject(App *ap, int posx, int posy, int w, int h, std::string image, BodyType type, float scaleX, float scaleY, int offsetX, int offsetY, bool debugRender) : RenderableObject(ap, posx, posy, w, h, image)
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
    scale.x=scaleX;
    scale.y=scaleY;
    offset.x=offsetX;
    offset.y=offsetY;
    bodyDef.position.Set(((float)posX + offset.x) / 100.0f, ((float)posY + offset.y) / 100.0f);
    body = app->getWorld()->CreateBody(&bodyDef);
    shape.SetAsBox((float)w * scale.x/ 100.0f / 2.0f, (float)h *scale.y/ 100.0f / 2.0f);
    fixtureDef.shape = &shape;
    if (type == DYNAMIC)
    {
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.3f;
    }
    body->CreateFixture(&fixtureDef);
    renderCollision = debugRender;
    colTexture = SDL_CreateTextureFromSurface(app->getRender(), IMG_Load("ColDebug.png"));
}

void PhysicsObject::update()
{

    b2Vec2 position = body->GetPosition();
    posX = position.x * 100 - offset.x;
    posY = position.y * 100 - offset.y;
    ang = body->GetAngle() * 180.0 / M_PI;
}

void PhysicsObject::render()
{
    if (renderCollision){
        SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_ADD);
        SDL_Rect dstrect = {posX + offset.x - width*scale.x / 2, posY + offset.y - height * scale.y / 2, width* scale.x, height * scale.y};
        SDL_Point center;
        center.x = width*scale.x / 2;
        center.y = height*scale.y / 2;
        SDL_RenderCopyEx(app->getRender(), colTexture, NULL, &dstrect, ang, &center, SDL_FLIP_NONE);
    }
    RenderableObject::render();
   
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