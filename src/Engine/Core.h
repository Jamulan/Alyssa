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

struct Settings { // the current state of user defined settings
    VkSampleCountFlagBits msaaSamples;
    VkBool32 Anisotropy;
    VkBool32 sampleRateShading;
    VkPolygonMode polygonMode;
};

class Core {
public:
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

    Settings settings;

    void initVulkan();
    void createInstance();
    void pickPhysicalDevice(VkSurfaceKHR *surface);
    void createLogicalDevice(VkSurfaceKHR *surface);
    void createCommandPool(VkSurfaceKHR surface);

    void cleanupVulkan();

    bool checkValidationLayerSupport();

public:
    VkInstance_T * getInstance() const;

    VkPhysicalDevice_T * getPhysicalDevice() const;

    VkDevice_T * getDevice() const;

    const Settings &getSettings() const;

    VkQueue_T *getGraphicsQueue() const;

    VkCommandPool_T *getCommandPool() const;

};


#endif //ALYSSA_CORE_H
