//
// Created by jamulan on 2020-11-11.
//

#ifndef ALYSSA_APPLICATION_H
#define ALYSSA_APPLICATION_H

#include <GLFW/glfw3.h>
#include <vector>
#include "Core.h"
#include "Util.h"



class Application {
public:
    void run();

    Application(Core *core);

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
    Core *core;
    VkSwapchainKHR swapChain;
    std::vector<VkImage> swapChainImages;
    std::vector<VkImageView> swapChainImageViews;
    std::vector<VkFramebuffer> swapChainFramebuffers;
    VkImage depthImage;
    VkDeviceMemory depthImageMemory;
    VkImageView depthImageView;
    VkImage colorImage;
    VkDeviceMemory colorImageMemory;
    VkImageView colorImageView;
    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;
    VkRenderPass renderPass;

    void initWindow();
    void createSurface();
    void createImageViews();
    void createSwapChain();
    void createRenderPass();
    void createColorResources();
    void createDepthResources();
    void createFrameBuffers();


    VkCommandBuffer beginSingleTimeCommands();
    void endSingleTimeCommands(VkCommandBuffer commandBuffer);
    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
    void createImage(uint32_t width, uint32_t height, uint32_t mipLevels, VkSampleCountFlagBits numSamples, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
    void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, uint32_t mipLevels);
    VkFormat findDepthFormat();
    VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
    bool hasStencilComponent(VkFormat format);
    VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, uint32_t mipLevels);

public:
    char *getAppName() const;

    uint32_t getAppVer() const;

    GLFWwindow *getWindow() const;

    VkSurfaceKHR_T *getSurface() const;

    const VkExtent2D &getSwapChainExtent() const;

    VkFormat getSwapChainImageFormat() const;

    Core *getCore() const;

    VkRenderPass_T *getRenderPass() const;

};


#endif //ALYSSA_APPLICATION_H
