//
// Created by jamulan on 2020-11-11.
//

#include <cstring>
#include <stdexcept>
#include <set>
#include "Core.h"

void Core::initVulkan() {
    createInstance();
    createSurface();
    pickPhysicalDevice();
    createLogicalDevice();
}

void Core::createInstance() {

    if(enableValidationLayers && !checkValidationLayerSupport()) {
        throw std::runtime_error("validation layers requested, but net availabe");
    }

    VkApplicationInfo appInfo = {
            .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
            .pApplicationName = application.getAppName(),
            .applicationVersion = application.getAppVer(),
            .pEngineName = "Alyssa",
            .engineVersion = VK_MAKE_VERSION(0, 0, 0),
            .apiVersion = VK_API_VERSION_1_0
    };

    VkInstanceCreateInfo createInfo = {
            .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
            .pApplicationInfo = &appInfo
    };
    if(enableValidationLayers) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();
    } else {
        createInfo.enabledLayerCount = 0;
    }

    uint32_t glfwExtensionCount = 0;
    const char **glfwExtensions;

    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;

    if(vkCreateInstance(&createInfo, nullptr, &instance ) != VK_SUCCESS) {
        throw std::runtime_error("failed to create instance!");
    }

    uint32_t extensionCount = 0;
    std::vector<VkExtensionProperties> extensions(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

    if(enableValidationLayers && extensionCount != 0) { // only print info if validation layers are enabled
        printf("available extensions:\n");
        for(const auto& extension : extensions) {
            printf("\t%s\n", extension.extensionName);
        }
    }
}

void Core::createSurface() {
    if(glfwCreateWindowSurface(instance, application.getWindow(), nullptr, &surface) != VK_SUCCESS) {
        throw std::runtime_error("failed to create window surface!");
    }
}

void Core::pickPhysicalDevice() {
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

    if(deviceCount == 0) {
        throw std::runtime_error("failed to find GPUs with Vulkan support!");
    }

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

    // TODO score available devices and pick the highest scored device
    for(const auto& device : devices) { // for now this just picks the first suitable device
        if(isDeviceSuitable(device, surface)) {
            physicalDevice = device;
            settings.msaaSamples = getMaxUsableSampleCount(device);
            break;
        }
    }

    if(physicalDevice == VK_NULL_HANDLE) {
        throw std::runtime_error("failed to find a suitable GPU!");
    }
}

void Core::createLogicalDevice() {

}

static bool checkValidationLayerSupport() {
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    for(const char* layerName : validationLayers) {
        bool layerFound = false;

        for(const auto &layerProperties : availableLayers) {
            if(strcmp(layerName, layerProperties.layerName) == 0) {
                layerFound = true;
                break;
            }
        }

        if(!layerFound) {
            return false;
        }
    }

    return true;
}

static VkSampleCountFlagBits getMaxUsableSampleCount(VkPhysicalDevice physicalDevice) {
    VkPhysicalDeviceProperties physicalDeviceProperties;
    vkGetPhysicalDeviceProperties(physicalDevice, &physicalDeviceProperties);

    VkSampleCountFlags counts = physicalDeviceProperties.limits.framebufferColorSampleCounts & physicalDeviceProperties.limits.framebufferDepthSampleCounts;
    if(counts & VK_SAMPLE_COUNT_64_BIT) { return VK_SAMPLE_COUNT_64_BIT; }
    if(counts & VK_SAMPLE_COUNT_32_BIT) { return VK_SAMPLE_COUNT_32_BIT; }
    if(counts & VK_SAMPLE_COUNT_16_BIT) { return VK_SAMPLE_COUNT_16_BIT; }
    if(counts & VK_SAMPLE_COUNT_8_BIT) { return VK_SAMPLE_COUNT_8_BIT; }
    if(counts & VK_SAMPLE_COUNT_4_BIT) { return VK_SAMPLE_COUNT_4_BIT; }
    if(counts & VK_SAMPLE_COUNT_2_BIT) { return VK_SAMPLE_COUNT_2_BIT; }

    return VK_SAMPLE_COUNT_1_BIT;
}

static bool isDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR surface) {
    VkPhysicalDeviceProperties deviceProperties;
    vkGetPhysicalDeviceProperties(device, &deviceProperties);

    QueueFamilyIndices indices = findQueueFamilies(device, surface);

    bool usable = deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU
                  && indices.isComplete() && checkDeviceExtensionSupport(device);

    if(usable) { // needs to check extension support first
        SwapChainSupportDetails swapChainSupport = querySwapChainSupport(device, surface);
        (!swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty()) ? usable = true : usable = false;
    }

    return usable;
}

bool QueueFamilyIndices::isComplete() {
    return graphicsFamily.has_value() && presentFamily.has_value();
}

static QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface) {
    QueueFamilyIndices indices;
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

    int i = 0;
    VkBool32 presentSupport = false;
    for(const auto& queueFamily : queueFamilies) {
        if(queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            indices.graphicsFamily = i;
        }

        presentSupport = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);

        if(presentSupport) {
            indices.presentFamily = i;
        }

        if(indices.isComplete()) {
            break;
        }

        i++;
    }



    return indices;
}

static SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surface) {
    SwapChainSupportDetails  details;

    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);

    uint32_t formatCount;
    vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);

    if(formatCount != 0) {
        details.formats.resize(formatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, details.formats.data());
    }

    uint32_t presentModeCount;
    vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);

    if(presentModeCount != 0) {
        details.presentModes.resize(presentModeCount);
        vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, details.presentModes.data());
    }

    return details;
}

static bool checkDeviceExtensionSupport(VkPhysicalDevice device) {
    uint32_t extensionCount;
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

    std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

    for(const auto& extension : availableExtensions) {
        requiredExtensions.erase(extension.extensionName);
    }

    return requiredExtensions.empty();
}
