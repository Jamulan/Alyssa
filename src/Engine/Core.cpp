//
// Created by jamulan on 2020-11-11.
//

#include <stdexcept>
#include <set>
#include "Core.h"

void Core::initVulkan() {
    createInstance();
    pickPhysicalDevice();
    createLogicalDevice();
}

void Core::createInstance() {

    if(enableValidationLayers && !checkValidationLayerSupport(validationLayers)) {
        throw std::runtime_error("validation layers requested, but net availabe");
    }

    VkApplicationInfo appInfo = {
            .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
            .pApplicationName = "Alyssa App 0",
            .applicationVersion = VK_MAKE_VERSION(0, 0, 0),
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

void Core::pickPhysicalDevice() {
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

    if(deviceCount == 0) {
        throw std::runtime_error("failed to find GPUs with Vulkan support!");
    }

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

    // TODO score available devices and pick the highest scored device
    for(const auto& tmpDevice : devices) { // for now this just picks the first suitable VkPhysicalDevice
        if(isDeviceSuitable(tmpDevice, *surface, deviceExtensions)) {
            physicalDevice = tmpDevice;
            settings.msaaSamples = getMaxUsableSampleCount(tmpDevice);
            break;
        }
    }

    if(physicalDevice == VK_NULL_HANDLE) {
        throw std::runtime_error("failed to find a suitable GPU!");
    }
}

void Core::createLogicalDevice() {
    QueueFamilyIndices indices = findQueueFamilies(physicalDevice, *surface);

    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    std::set<uint32_t> uniqueQueueFamilies = {indices.graphicsFamily.value(), indices.presentFamily.value()};

    float queuePriority = 1.0f;
    for (uint32_t queueFamily : uniqueQueueFamilies) {
        VkDeviceQueueCreateInfo queueCreateInfo{};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = queueFamily;
        queueCreateInfo.queueCount = 1;
        queueCreateInfo.pQueuePriorities = &queuePriority;
        queueCreateInfos.push_back(queueCreateInfo);
    }

    VkPhysicalDeviceFeatures deviceFeatures{}; // every thing will be VK_FALSE for now
    deviceFeatures.samplerAnisotropy = settings.Anisotropy;
    deviceFeatures.sampleRateShading = settings.sampleRateShading;

    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

    createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
    createInfo.pQueueCreateInfos = queueCreateInfos.data();

    createInfo.pEnabledFeatures = &deviceFeatures;

    createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
    createInfo.ppEnabledExtensionNames = deviceExtensions.data();

    if(enableValidationLayers) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();
    } else {
        createInfo.enabledLayerCount = 0;
    } // end of ignored section

    if(vkCreateDevice(physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS) {
        throw std::runtime_error("failed to create logical device!");
    }

    vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, &graphicsQueue);
    vkGetDeviceQueue(device, indices.presentFamily.value(), 0, &presentQueue);
}


VkInstance_T * Core::getInstance() const {
    return instance;
}

VkPhysicalDevice_T * Core::getPhysicalDevice() const {
    return physicalDevice;
}

VkDevice_T * Core::getDevice() const {
    return device;
}

