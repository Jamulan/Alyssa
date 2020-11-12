//
// Created by jamulan on 2020-11-11.
//

#ifndef ALYSSA_APPLICATION_H
#define ALYSSA_APPLICATION_H

#include <GLFW/glfw3.h>
#include <vector>
#include "World.h"


class Application {
public:
    void run();

private:
    char* appName;
    uint32_t appVer;
    uint32_t width;
    uint32_t height;
    GLFWwindow* window;

    World currWorld;
    std::vector<World> worlds;

    void initWindow();

public:
    char *getAppName() const;

    uint32_t getAppVer() const;

    GLFWwindow *getWindow() const;

};


#endif //ALYSSA_APPLICATION_H
