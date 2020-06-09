#include "MainMenu.h"
#include "MenuButton.h"

MainMenu::MainMenu(App* ap):GameState(ap){
}

void MainMenu::start(){
    objects.push_back(new MenuButton(app, 320, 240, 200, 100, "koji.jpeg"));
}