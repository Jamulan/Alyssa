//
// Created by jamulan on 2020-11-11.
//

#ifndef ALYSSA_CORE_H
#define ALYSSA_CORE_H

#include <vulkan/vulkan.h>
#include <vector>
#include <optional>
#include "Util.h"


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

private:
    const bool enableValidationLayers = true;
    VkInstance instance;
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkDevice device;
    VkQueue graphicsQueue; // may need to be expanded to a vector
    VkQueue presentQueue;
    VkSurfaceKHR* surface; // obtain from application somehow

    Settings settings;

    void initVulkan();
    void createInstance();
    void pickPhysicalDevice();
    void createLogicalDevice();

    void cleanupVulkan();

public:
    VkInstance_T * getInstance() const;

    VkPhysicalDevice_T * getPhysicalDevice() const;

    VkDevice_T * getDevice() const;

};


#endif //ALYSSA_CORE_H
