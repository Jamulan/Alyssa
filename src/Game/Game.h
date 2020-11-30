//
// Created by jamulan on 2020-11-29.
//

#ifndef ALYSSA_GAME_H
#define ALYSSA_GAME_H


#include "Level.h"

class Game {
public:
    Game(int width, int height, Settings settings);
    void loadLevel(Level *level);
    void startLevel();

private:
    GLFWwindow *window;
    Core *core;
    Application *app;
    Material *mainMaterial;
    Level *currentLevel;
};


#endif //ALYSSA_GAME_H
