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
#include <stb_image.h>

#define MAX_FRAMES_IN_FLIGHT 3

struct Vertex {
    glm::vec3 pos;
    glm::vec3 color;
    glm::vec2 texCoord;
    static VkVertexInputBindingDescription getBindingDescription();
    static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions();
    bool operator==(const Vertex& other) const;
};
namespace std {
    template<> struct hash<Vertex> {
        size_t operator()(Vertex const &vertex) const;
    };
}

struct ModelInfo { // PositionRotationScale needs better name
    glm::vec3 pos;
    glm::vec3 rot; // TODO convert to quaternions
    float angle;
    glm::vec3 sca;

    std::vector<VkCommandBuffer> *commandBuffers;
    std::vector<VkDeviceMemory> *uniformBuffersMemory;

    glm::mat4 getMat4();
};

struct Settings { // the current state of user defined settings
    VkSampleCountFlagBits msaaSamples;
    VkBool32 Anisotropy;
    float maxAnisotropy;
    VkBool32 sampleRateShading;
    VkPolygonMode polygonMode;
    uint32_t maxMipLevels;
    float minFrametime;
};

struct UniformBufferObject {
    alignas(16) glm::mat4 model;
    alignas(16) glm::mat4 view;
    alignas(16) glm::mat4 proj;
};

std::vector<char> readFile(const std::string& filename);
VkShaderModule createShaderModule(const std::string& filename);

VkCommandBuffer beginSingleTimeCommands(VkDevice device, VkCommandPool commandPool);
void
endSingleTimeCommands(VkDevice device, VkQueue graphicsQueue, VkCommandPool commandPool, VkCommandBuffer commandBuffer);
void
transitionImageLayout(VkDevice device, VkQueue graphicsQueue, VkCommandPool commandPool, VkImage image, VkFormat format,
                      VkImageLayout oldLayout, VkImageLayout newLayout, uint32_t mipLevels);
bool hasStencilComponent(VkFormat format);
void createImage(VkPhysicalDevice physicalDevice, VkDevice device, uint32_t width, uint32_t height, uint32_t mipLevels,
                 VkSampleCountFlagBits numSamples, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage,
                 VkMemoryPropertyFlags properties, VkImage &image, VkDeviceMemory &imageMemory);
VkImageView createImageView(VkDevice device, VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, uint32_t mipLevels);
void generateMipmaps(VkPhysicalDevice physicalDevice, VkQueue graphicsQueue, VkDevice device,
                     VkCommandPool commandPool, VkImage image, VkFormat imageFormat, int32_t texWidth,
                     int32_t texHeight, uint32_t mipLevels);
void copyBufferToImage(VkDevice device, VkCommandPool commandPool, VkQueue graphicsQueue, VkBuffer buffer, VkImage image,
                       uint32_t width, uint32_t height);
void copyBuffer(VkDevice device, VkQueue graphicsQueue, VkCommandPool commandPool, VkBuffer srcBuffer, VkBuffer dstBuffer,
                VkDeviceSize size);
uint32_t findMemoryType(VkPhysicalDevice physicalDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties);
void createBuffer(VkDevice device, VkPhysicalDevice physicalDevice, VkDeviceSize size, VkBufferUsageFlags usage,
                  VkMemoryPropertyFlags properties, VkBuffer &buffer, VkDeviceMemory &bufferMemory);


#endif //ALYSSA_UTIL_H
