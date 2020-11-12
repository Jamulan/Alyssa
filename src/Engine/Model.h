//
// Created by jamulan on 2020-11-11.
//

#ifndef ALYSSA_MODEL_H
#define ALYSSA_MODEL_H

#include <vulkan/vulkan.h>
#include <glm/glm.hpp>
#include <vector>
#include <array>

struct Vertex {
    glm::vec3 pos;
    glm::vec3 color;
    glm::vec2 texCoord;
    static VkVertexInputBindingDescription getBindingDescription();
    static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions();
    bool operator==(const Vertex& other) const;
};

class Model {
public:

private:
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;
    VkBuffer indexBuffer;
    VkDeviceMemory indexBufferMemory;
    std::vector<VkBuffer> uniformBuffers;
    std::vector<VkDeviceMemory> uniformBuffersMemory;
    std::vector<VkCommandBuffer> commandBuffers;

};


#endif //ALYSSA_MODEL_H
