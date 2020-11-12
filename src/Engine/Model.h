//
// Created by jamulan on 2020-11-11.
//

#ifndef ALYSSA_MODEL_H
#define ALYSSA_MODEL_H

#include <vulkan/vulkan.h>
#include <glm/glm.hpp>
#include <vector>
#include <array>

#include "Util.h"
#include "Material.h"

class Model {
public:

private:
    Material material;
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;
    VkBuffer indexBuffer;
    VkDeviceMemory indexBufferMemory;
    std::vector<VkBuffer> uniformBuffers;
    std::vector<VkDeviceMemory> uniformBuffersMemory;
    std::vector<VkCommandBuffer> commandBuffers;


public:
    const Material &getMaterial() const;
};


#endif //ALYSSA_MODEL_H
