//
// Created by jamulan on 2020-11-29.
//

#ifndef ALYSSA_ENTITY_H
#define ALYSSA_ENTITY_H


#include "Game.h"
#include "../Engine/Model.h"

class Entity {
public:
    Entity(Game *game, const std::string &textureFilename, const std::string &modelFilename, LocOri locOri);

private:
    Model *model;
    Game *game;
    LocOri *locOri;

};


#endif //ALYSSA_ENTITY_H
