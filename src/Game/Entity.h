//
// Created by jamulan on 2020-11-29.
//

#ifndef ALYSSA_ENTITY_H
#define ALYSSA_ENTITY_H


#include "../Engine/Model.h"

class Entity {
    void update();
    void load();

private:
    Model model;

};


#endif //ALYSSA_ENTITY_H
