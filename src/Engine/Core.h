//
// Created by jamulan on 2020-11-11.
//

#ifndef ALYSSA_CORE_H
#define ALYSSA_CORE_H

#include <vulkan/vulkan.h>
#include <vector>
#include <optional>
#include "Util.h"


struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;
    bool isComplete();
};

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

class Core {
public:
    Core(GLFWwindow *window, Settings settings);

    const std::vector<const char*> validationLayers = {
            "VK_LAYER_KHRONOS_validation"
    };
    const std::vector<const char*> deviceExtensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

    bool isDeviceSuitable(VkSurfaceKHR surface);
    QueueFamilyIndices findQueueFamilies(VkSurfaceKHR surface);
    VkSampleCountFlagBits getMaxUsableSampleCount();
    bool checkDeviceExtensionSupport();
    SwapChainSupportDetails querySwapChainSupport(VkSurfaceKHR surface);

private:
    const bool enableValidationLayers = true;
    VkInstance instance;
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkDevice device;
    VkQueue graphicsQueue; // may need to be expanded to a vector
    VkQueue presentQueue;
    VkCommandPool commandPool;
    GLFWwindow *window;
    VkSurfaceKHR surface;

    Settings settings;

    void initVulkan();
    void createInstance();
    void pickPhysicalDevice();
    void createLogicalDevice();
    void createCommandPool();

    void cleanupVulkan();

    bool checkValidationLayerSupport();

public:
    VkInstance_T * getInstance() const;

    VkPhysicalDevice_T * getPhysicalDevice() const;

    VkDevice_T * getDevice();

    const Settings &getSettings() const;

    VkQueue_T *getGraphicsQueue() const;

    VkQueue_T * getPresentQueue() const;

    VkCommandPool getCommandPool() const;

    GLFWwindow *getWindow() const;

    VkSurfaceKHR getSurface() const;

};


#endif //ALYSSA_CORE_H
