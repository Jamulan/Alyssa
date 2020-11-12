//
// Created by jamulan on 2020-11-11.
//

#ifndef ALYSSA_CORE_H
#define ALYSSA_CORE_H

#include <vulkan/vulkan.h>
#include <vector>
#include <optional>
#include "Application.h"

const std::vector<const char*> validationLayers = {
        "VK_LAYER_KHRONOS_validation"
};
static bool checkValidationLayerSupport();
const std::vector<const char*> deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
};
static bool checkDeviceExtensionSupport(VkPhysicalDevice);

struct Settings { // the current state of user defined settings
    VkSampleCountFlagBits msaaSamples;
};
static bool isDeviceSuitable(VkPhysicalDevice, VkSurfaceKHR);
static VkSampleCountFlagBits getMaxUsableSampleCount(VkPhysicalDevice);

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;
    bool isComplete();
};
static QueueFamilyIndices findQueueFamilies(VkPhysicalDevice, VkSurfaceKHR);

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};
static SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice, VkSurfaceKHR);

class Core {
public:
    Core();

private:
    const bool enableValidationLayers = true;
    VkInstance instance;
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkDevice device;
    VkSurfaceKHR surface;

    Settings settings;
    Application application;

    void initVulkan();
    void createInstance();
    void createSurface();
    void pickPhysicalDevice();
    void createLogicalDevice();

    void cleanup();

};


#endif //ALYSSA_CORE_H
