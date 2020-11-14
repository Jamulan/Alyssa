//
// Created by jamulan on 2020-11-12.
//

#include <cstring>
#include <fstream>
#include <GLFW/glfw3.h>
#include "Util.h"

// TODO if only used by a single class add it to that class

VkVertexInputBindingDescription Vertex::getBindingDescription() {
    VkVertexInputBindingDescription bindingDescription{};
    bindingDescription.binding = 0;
    bindingDescription.stride = sizeof(Vertex);
    bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

    return bindingDescription;
}

std::array<VkVertexInputAttributeDescription, 3> Vertex::getAttributeDescriptions() {
    std::array<VkVertexInputAttributeDescription, 3> attributeDestriptions{};
    attributeDestriptions[0].binding = 0;
    attributeDestriptions[0].location = 0;
    attributeDestriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
    attributeDestriptions[0].offset = offsetof(Vertex, pos);

    attributeDestriptions[1].binding = 0;
    attributeDestriptions[1].location = 1;
    attributeDestriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
    attributeDestriptions[1].offset = offsetof(Vertex, color);

    attributeDestriptions[2].binding = 0;
    attributeDestriptions[2].location = 2;
    attributeDestriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
    attributeDestriptions[2].offset = offsetof(Vertex, texCoord);

    return attributeDestriptions;
}

bool Vertex::operator==(const Vertex &other) const {
    return pos == other.pos && color == other.color && texCoord == other.texCoord;
}

std::vector<char> readFile(const std::string &filename) {
    std::ifstream file(filename, std::ios::ate | std::ios::binary);

    if(!file.is_open()) {
        throw std::runtime_error("failed to open file!");
    }

    size_t fileSize = (size_t) file.tellg();
    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);

    file.close();

    return buffer;
}


