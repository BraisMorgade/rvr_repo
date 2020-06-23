#ifndef GameObject_h
#define GameObject_h
#include <SDL2/SDL.h>
#include <string>
#include "Serializable.h"

class App;

class GameObject: public Serializable{
public:
    GameObject(App* ap){app=ap; readyDestr=false; tag="Unnamed";};
    virtual ~GameObject(){};
    virtual void start(){}
    virtual void update(){};
    virtual void render(){};
    virtual void setTag(std::string t){tag=t;};
    virtual std::string getTag(){return tag;};
    virtual bool isReadyToDestroy(){return readyDestr;};
    virtual void readyToDestroy(bool ready){
        readyDestr=ready;
    };
    virtual void handleInput(SDL_Event& event){};
    virtual void to_bin() override{};
    virtual int from_bin(char* data) override {
        return 0;
    };
    
protected:
    App* app;
    bool readyDestr;
    std::string tag;
};
#endif