//
// Created by jamulan on 2020-11-29.
//

#ifndef ALYSSA_GAME_H
#define ALYSSA_GAME_H


#include "../Engine/Util.h"
#include "../Engine/Material.h"
#include "Entity.h"

class Game {
public:
    Game(int width, int height, Settings settings);
    Material *getMainMaterial();

private:
    GLFWwindow *window;
    Core *core;
    Application *app;
    Material *mainMaterial;
};


#endif //ALYSSA_GAME_H
