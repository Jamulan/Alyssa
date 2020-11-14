//
// Created by jamulan on 2020-11-11.
//

#ifndef ALYSSA_MATERIAL_H
#define ALYSSA_MATERIAL_H


#include <vulkan/vulkan.h>
#include "Application.h"

class Material {
public:

private:
    Settings settings;
    VkDescriptorSetLayout descriptorSetLayout;
    VkPipelineLayout pipelineLayout;
    VkPipeline graphicsPipeline;
    VkShaderModule vertShaderModule;
    VkShaderModule fragShaderModule;
    Application *application;

    void createDescriptorSetLayout();
    void createGraphicsPipeline();
};


#endif //ALYSSA_MATERIAL_H
