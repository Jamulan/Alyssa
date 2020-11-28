//
// Created by jamulan on 2020-11-11.
//

#ifndef ALYSSA_MATERIAL_H
#define ALYSSA_MATERIAL_H


#include <vulkan/vulkan.h>
#include "Application.h"

class Material {
public:
    Material(Application *application, Settings settings, std::string vertShaderFilename,
             std::string fragShaderFilename);

    void registerModel(ModelInfo *info);

    Application *getApplication() const;

    const Settings &getSettings() const;

private:
    Settings settings;
    VkPipelineLayout pipelineLayout;
    VkPipeline graphicsPipeline;
    VkShaderModule vertShaderModule;
    VkShaderModule fragShaderModule;
    Application *application;
    std::vector<ModelInfo *> models;
    std::vector<VkCommandBuffer> commandBuffers;

    VkShaderModule createShaderModule(const std::vector<char>& code);
    void createCommandBuffers();
    void createGraphicsPipeline();

public:
    VkPipeline_T *getGraphicsPipeline() const;

    VkPipelineLayout_T *getPipelineLayout() const;
};


#endif //ALYSSA_MATERIAL_H
