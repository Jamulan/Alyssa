//
// Created by jamulan on 2020-11-29.
//

#ifndef ALYSSA_LEVEL_H
#define ALYSSA_LEVEL_H


#include "../Engine/Model.h"
#include "Entity.h"

struct LevelState {
    std::string *modelName;
};

class Level : Entity {
public:
    void addEntity(Entity entity);

private:
    LevelState currentState;
    std::vector<Entity *> entities;
};


#endif //ALYSSA_LEVEL_H
