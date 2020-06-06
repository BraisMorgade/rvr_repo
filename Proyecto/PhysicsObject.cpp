#include "PhysicsObject.h"
#include "App.h"
#include "box2d/b2_world.h"

PhysicsObject::PhysicsObject(App* ap, int posx, int posy, int w, int h, std::string image):RenderableObject(ap, posx, posy, h, w, image){
    
    bodyDef.type= b2_dynamicBody;
    bodyDef.position.Set(posX/100, posY/100);
    body= app->getWorld()->CreateBody(&bodyDef);
    dynamicBox.SetAsBox((float)w/100.0f/2.0f, (float)h/100.0f/2.0f);
    fixtureDef.shape=&dynamicBox;
    fixtureDef.density=1.0f;
    fixtureDef.friction=0.3f;
    body->CreateFixture(&fixtureDef);
}

void PhysicsObject::update(){
   
    b2Vec2 position = body->GetPosition();
    posX = position.x;
    posY = position.y;
}