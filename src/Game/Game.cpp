//
// Created by jamulan on 2020-11-29.
//

#include "Game.h"

Game::Game(int width, int height, Settings settings) {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    window = glfwCreateWindow(width, height, "Alyssa", nullptr, nullptr);
    Core c = Core(window, settings);
    core = &c;
    Application a = Application(core, window);
    app = &a;
    Material m = Material(app, settings, "assets/shaders/vert.spv", "assets/shaders/vert.spv");
    mainMaterial = &m;
    currentLevel = nullptr;
}

void Game::loadLevel(Level *level) {
    currentLevel = level;
}
