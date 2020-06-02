#pragma once
#include <list>
#include "GameObject.h"

class GameState{
public:
    GameState();
    ~GameState();
    void start();
    void update();
    void render(SDL_Renderer* render);
    void handleInput(SDL_Event& event);
    void end();
protected:
    std::list<GameObject*> objects;
};
