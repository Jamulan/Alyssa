//
// Created by jamulan on 2020-11-11.
//

#ifndef ALYSSA_APPLICATION_H
#define ALYSSA_APPLICATION_H

#include <GLFW/glfw3.h>
#include <vector>
#include "Core.h"
#include "World.h"
#include "Util.h"


struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

bool QueueFamilyIndices::isComplete() {
    return graphicsFamily.has_value() && presentFamily.has_value();
}


class Application {
public:
    void run();
    void init(Core *core);

    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities);

private:
    char* appName;
    uint32_t appVer;
    uint32_t width;
    uint32_t height;
    VkSurfaceKHR surface;
    GLFWwindow* window; // one window = one Application, if I need another window make a separate Application
    VkSwapchainKHR swapChain;
    std::vector<VkImage> swapChainImages;
    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;

    World world;

    void initWindow();
    void createSurface(Core *core);
    void createSwapChain(Core *core);

public:
    char *getAppName() const;

    uint32_t getAppVer() const;

    GLFWwindow *getWindow() const;

    VkSurfaceKHR_T *getSurface() const;

};


#endif //ALYSSA_APPLICATION_H
