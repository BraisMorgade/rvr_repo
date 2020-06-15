#include "HitDetectionBox.h"

HitDetectionBox::HitDetectionBox(App* ap, int posx, int posy,
    int w, int h, float scaleX, float scaleY,
    int offsetX, int offsetY, bool debugRender, 
    BoxType bType, Fighter* fighter): PhysicsObject(ap, posx, posy, w, h,
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