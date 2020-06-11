#ifndef AnimationMachine_h
#define AnimationMachine_h

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>

struct AnimInfo{
    int beginningX;
    int beginningY;
    int nframes;
    float animTime;
    bool loop;
};

class AnimationMachine{
public:
    AnimationMachine(int nCols, int nRows, SDL_Rect* clip);
    ~AnimationMachine();
    void addAnimation(std::string name, AnimInfo info);
    void playAnimation(std::string name);
    void updateAnimation();
private:
    int nCols, nRows;
    int frame;
    float timeSinceLastFrame;
    std::map<std::string, AnimInfo> animations;
    AnimInfo currentAnimation;
    SDL_Rect* clip;
};





#endif