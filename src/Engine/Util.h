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

struct Vertex {
    glm::vec3 pos;
    glm::vec3 color;
    glm::vec2 texCoord;
    static VkVertexInputBindingDescription getBindingDescription();
    static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions();
    bool operator==(const Vertex& other) const;
};

static std::vector<char> readFile(const std::string& filename);
static VkShaderModule createShaderModule(const std::string& filename);


#endif //ALYSSA_UTIL_H
