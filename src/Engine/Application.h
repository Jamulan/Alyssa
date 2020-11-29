//
// Created by jamulan on 2020-11-11.
//

#ifndef ALYSSA_APPLICATION_H
#define ALYSSA_APPLICATION_H

#include <GLFW/glfw3.h>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include "Core.h"
#include <chrono>

class Application {
public:
    void run();

    Application(Core *core, GLFWwindow *window);
    void registerModel(ModelInfo *info);
    void addCommandBuffers(std::vector<VkCommandBuffer> buffers);

    void setView(float rotX, float rotY, float fov);

    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities);

private:
    char* appName;
    uint32_t appVer;
    float width;
    float height;
    bool viewportChanged;
    float bearing; // in degrees
    float tilt; // in degrees
    float FOV;
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
    VkDescriptorSetLayout descriptorSetLayout;

    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence> inFlightFences;
    std::vector<VkFence> imagesInFlight;

    std::vector<ModelInfo*> modelInfos;
    std::vector<std::vector<VkCommandBuffer>> buffersToSubmit;
    size_t currentFrame;

    float lastTime;
    float minFrametime;

    void drawFrame();
    void updateUniformBuffers(uint32_t currentImage);

    void createImageViews();
    void createSwapChain();
    void createRenderPass();
    void createColorResources();
    void createDepthResources();
    void createFrameBuffers();
    void createDescriptorSetLayout();
    void createSyncObjects();



    void createImage(uint32_t width, uint32_t height, uint32_t mipLevels, VkSampleCountFlagBits numSamples, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
    VkFormat findDepthFormat();
    VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);

public:
    char *getAppName() const;

    uint32_t getAppVer() const;

    std::vector<VkImage> &getSwapChainImages();

    const VkExtent2D &getSwapChainExtent() const;

    VkFormat getSwapChainImageFormat() const;

    Core *getCore() const;

    VkRenderPass_T *getRenderPass() const;

    VkDescriptorSetLayout const * getDescriptorSetLayout() const;

    const std::vector<VkFramebuffer> &getSwapChainFramebuffers() const;

    float * getWidth();
    float * getHeight();

};


#endif //ALYSSA_APPLICATION_H
