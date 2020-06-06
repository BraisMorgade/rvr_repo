#include "GameObjectTest.h"
#include "SDL2/SDL_image.h"
#include "App.h"
#include "box2d/b2_world.h"

GameObjectTest::GameObjectTest(App* ap, int posx, int posy, int w, int h):GameObject(ap)
{
    texture = nullptr;
    posX = posx;
    posY = posy;
    width = w;
    height = h;
    SDL_Surface *surface = IMG_Load("koji.jpeg");
    if (app->getRender() != nullptr)
        texture = SDL_CreateTextureFromSurface(app->getRender(), surface);
    bodyDef.type= b2_dynamicBody;
    bodyDef.position.Set(posX/100, posY/100);
    body= app->getWorld()->CreateBody(&bodyDef);
    dynamicBox.SetAsBox(w/100/2, h/100/2);
    fixtureDef.shape=&dynamicBox;
    fixtureDef.density=1.0f;
    fixtureDef.friction=0.3f;
    body->CreateFixture(&fixtureDef);
    
}
void GameObjectTest::update(){
    b2Vec2 position = body->GetPosition();
    posX= position.x;
    posY= position.y;
}
void GameObjectTest::render()
{
    if (texture != nullptr)
    {
        SDL_Rect dstrect = {posX, posY, width, height};
        SDL_RenderCopy(app->getRender(), texture, NULL, &dstrect);
    }
}