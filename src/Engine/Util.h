//
// Created by jamulan on 2020-11-12.
//

#ifndef ALYSSA_UTIL_H
#define ALYSSA_UTIL_H

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include <optional>
#include <set>
#include <string>
#include <array>

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

struct Vertex {
    glm::vec3 pos;
    glm::vec3 color;
    glm::vec2 texCoord;
    static VkVertexInputBindingDescription getBindingDescription();
    static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions();
    bool operator==(const Vertex& other) const;
};


static bool checkValidationLayerSupport(std::vector<const char*> validationLayers);
static VkSampleCountFlagBits getMaxUsableSampleCount(VkPhysicalDevice device);
static bool isDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR surface, std::vector<const char*> deviceExtensions);
static QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface);
static SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surface);
static bool checkDeviceExtensionSupport(VkPhysicalDevice device, std::vector<const char *> deviceExtensions);
static std::vector<char> readFile(const std::string& filename);
static VkShaderModule createShaderModule(const std::string& filename);
static VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
static VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
static VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities, GLFWwindow *window);


#endif //ALYSSA_UTIL_H
