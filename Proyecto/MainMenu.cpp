#include "MainMenu.h"
#include "MenuButton.h"

MainMenu::MainMenu(App* ap):GameState(ap){
    objects.push_back(new MenuButton(app, 220, 190, 200, 100, "koji.jpeg"));
}