//
// Created by jamulan on 2020-11-11.
//

#include <cstdio>
#include "Engine/Core.h"
#include "Engine/Application.h"
#include "Engine/Material.h"
#include "Engine/Model.h"

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    GLFWwindow *window = glfwCreateWindow(800, 600, "Alyssa-Demo", nullptr, nullptr);
    Settings settings = {
            .msaaSamples = VK_SAMPLE_COUNT_2_BIT,
            .Anisotropy = VK_FALSE,
            .maxAnisotropy = 1.0f,
            .sampleRateShading = VK_FALSE,
            .polygonMode = VK_POLYGON_MODE_FILL,
            .maxMipLevels = 3,
            .minFrametime = 5.0f,
    };
    Core core = Core(window, settings);
    Application app = Application(&core, window);
    Material material = Material(&app, settings, std::string(), std::string());
    auto update = [](float timeMS) -> glm::mat4 {
        return glm::rotate(glm::mat4(1.0f), glm::radians(30.0f*(timeMS/1000.0f)), glm::vec3(0.0f, 0.0f, 1.0f));
    };
    ModelInfo modelInfo = {
            .pos = glm::vec3(0.0f, 0.0f, -0.5f),
            .rot = glm::vec3(0.0f, 0.0f, 1.0f),
            .angle = 0.0f,
            .sca = glm::vec3(0.5f),
            .update = update,
    };
    Model model = Model(&material, "assets/textures/Dodecahedron.png", "assets/models/Dodecahedron.obj", modelInfo);
    app.run();
}