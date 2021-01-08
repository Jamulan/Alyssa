//
// Created by jamulan on 2020-11-29.
//

#include "Entity.h"

Entity::Entity(Game *game, const std::string &textureFilename, const std::string &modelFilename, LocOri locOri) {
    this->game = game;
    ModelInfo modelInfo = {};
    modelInfo.stuff = locOri;
    Model m = Model(game->getMainMaterial(), textureFilename, modelFilename, modelInfo);
    model = &m;

    this->locOri = model->getStuff();
}

