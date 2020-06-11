#include "AnimationMachine.h"
#include <iostream>

AnimationMachine::AnimationMachine(int cols, int rows, SDL_Rect *clp)
{
    nCols = cols;
    nRows = rows;
    clip = clp;
}

AnimationMachine::~AnimationMachine()
{
}

void AnimationMachine::addAnimation(std::string name, AnimInfo info)
{
    animations[name] = info;
}

void AnimationMachine::playAnimation(std::string name)
{
    currentAnimation = animations[name];
    frame = 0;
    timeSinceLastFrame = SDL_GetTicks()/1000.0f;
    clip->x = currentAnimation.beginningX;
    clip->y = currentAnimation.beginningY;
}

void AnimationMachine::updateAnimation()
{
    float frameTime = (float)currentAnimation.animTime / (float)currentAnimation.nframes;

    if (SDL_GetTicks()/1000.0f - timeSinceLastFrame >= frameTime)
    {
        if (frame < currentAnimation.nframes -1){
            clip->x = (clip->x + clip->w) % (nCols * clip->w);
            frame++;
            timeSinceLastFrame = SDL_GetTicks()/1000.0f;

        }
        else if(currentAnimation.loop){
            frame=0;
            timeSinceLastFrame = SDL_GetTicks()/1000.0f;
            clip->x=currentAnimation.beginningX;
            clip->y=currentAnimation.beginningY;
        }

    }
    
}
