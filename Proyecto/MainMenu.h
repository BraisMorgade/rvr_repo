#ifndef MainMenu_h
#define MainMenu_h

#include "GameState.h"

class App;

class MainMenu: public GameState{
public:
    MainMenu(App* ap);
    ~MainMenu();
    virtual void start();
    virtual void send() override;
    virtual void receive() override;
    bool joining=false;
    bool creating=false;
};

#endif