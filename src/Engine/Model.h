//
// Created by jamulan on 2020-11-11.
//

#ifndef ALYSSA_MODEL_H
#define ALYSSA_MODEL_H

#include <vulkan/vulkan.h>
#include <vector>
#include <array>
#include <tiny_obj_loader.h>

#include "Material.h"
#include "Util.h"

class Model {
public:
    Model(Material *material, const std::string &textureFilename, const std::string &modelFilename,
          ModelInfo info);

    LocOri* getStuff();

private:
    Material *material;
    std::string textureFilename;
    std::string modelFilename;
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;
    VkBuffer indexBuffer;
    VkDeviceMemory indexBufferMemory;
    std::vector<VkBuffer> uniformBuffers;
    std::vector<VkDeviceMemory> uniformBuffersMemory;
    VkImage textureImage;
    VkDeviceMemory textureImageMemory;
    VkImageView textureImageView;
    uint32_t mipLevels;
    VkSampler textureSampler;
    VkDescriptorPool descriptorPool;
    std::vector<VkDescriptorSet> descriptorSets;

    ModelInfo modelInfo;

    void createTextureImage();
    void createTextureImageView();
    void createTextureSampler();
    void loadModel();
    void createVertexBuffer();
    void createIndexBuffer();
    void createUniformBuffers();
    void createDescriptorPool();
    void createDescriptorSets();
};


#endif //ALYSSA_MODEL_H
