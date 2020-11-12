//
// Created by jamulan on 2020-11-11.
//

#ifndef ALYSSA_MATERIAL_H
#define ALYSSA_MATERIAL_H


#include <vulkan/vulkan.h>
#include "Util.h"

class Material {
public:

private:
    VkPipeline graphicsPipeline;
    VkShaderModule vertShaderModule;
    VkShaderModule fragShaderModule;

    void createGraphicsPipeline();
};


#endif //ALYSSA_MATERIAL_H
