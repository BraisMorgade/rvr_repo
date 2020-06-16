#include "HitDetectionBox.h"
#include "Fighter.h"

HitDetectionBox::HitDetectionBox(App* ap, int w, int h, 
    float scaleX, float scaleY,
    int offsetX, int offsetY, bool debugRender, 
    BoxType bType, Fighter* fighter): PhysicsObject(ap, fighter->getPositionX(), fighter->getPositionY(), w, h,
    "", TRIGGER, scaleX, scaleY, offsetX, offsetY, debugRender){

    fg=fighter;
    boxType=bType;
}

void HitDetectionBox::OnCollisionEnter(PhysicsObject* other){
    HitDetectionBox* otherBox=static_cast<HitDetectionBox*>(other);
    /*if(boxType==HITBOX){
        otherBox->fg->damage();
        if(otherBox->boxType==HITBOX){
            fg->damage();
        }
    }
    
    else if(other->boxType==HITBOX){
        fg->damage();
    }
    */
}

void HitDetectionBox::OnCollisionExit(PhysicsObject* other){

}

void HitDetectionBox::update(){
    PhysicsObject::update();
    posX=fg->getPositionX();
    posY=fg->getPositionY();
    body->SetTransform(b2Vec2((float)(fg->getPositionX() + offset.x)/100.0f,
    (float)(fg->getPositionY() + offset.y)/100.0f), body->GetAngle());
}