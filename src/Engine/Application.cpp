//
// Created by jamulan on 2020-11-11.
//

#define GLFW_INCLUDE_VULKAN

#include "Application.h"

void Application::initWindow() {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    window = glfwCreateWindow(width, height, appName, nullptr, nullptr);
}



char *Application::getAppName() const {
    return appName;
}

uint32_t Application::getAppVer() const {
    return appVer;
}

GLFWwindow *Application::getWindow() const {
    return window;
}
