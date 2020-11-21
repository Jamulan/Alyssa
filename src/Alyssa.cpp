//
// Created by jamulan on 2020-11-11.
//

#include <cstdio>
#include <thread>
#include "Engine/Core.h"
#include "Engine/Application.h"
#include "Engine/Material.h"
#include "Engine/Model.h"

static auto startTime = std::chrono::high_resolution_clock::now();

class Update {
public:
    Update(bool *go) : go(go) {
        stuffs = {};
    }

    std::vector<LocOri*> stuffs;
    bool *go;
    void updateModels() {
        while(*go) {
            float t = std::chrono::duration<float, std::chrono::milliseconds::period>(
                    std::chrono::high_resolution_clock::now() - startTime).count();
            for(LocOri* stuff : stuffs) {
                stuff->rot = glm::vec3(0.0f, 0.0f, 1.0f);
                stuff->angle = glm::radians(1.0f * t);
            }
        }
    }
};

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
            .minFrametime = 5.0f
    };
    Core core = Core(window, settings);
    Application app = Application(&core, window);
    Material material = Material(&app, settings, "assets/shaders/vert.spv", "assets/shaders/frag.spv");
    LocOri stuff = {
            .pos = glm::vec3(0.0f, 0.0f, -0.5f),
            .rot = glm::vec3(0.0f, 0.0f, 1.0f),
            .angle = 0.0f,
            .sca = glm::vec3(0.5f)
    };
    ModelInfo modelInfo = {
            .stuff = stuff
    };
    Model model = Model(&material, "assets/textures/Dodecahedron.png", "assets/models/Dodecahedron.obj", modelInfo);
    LocOri stuff0 = {
            .pos = glm::vec3(0.0f, 0.0f, -2.0f),
            .rot = glm::vec3(1.0f, 0.0f, 0.0f),
            .angle = glm::radians(90.0f),
            .sca = glm::vec3(0.5f)
    };
    ModelInfo modelInfo0 = {
            .stuff = stuff0
    };
    Model model0 = Model(&material, "assets/textures/tmpFloor.png", "assets/models/tmpFloor.obj", modelInfo0);
    std::thread graphicsThread(&Application::run, &app);

    bool go = true;

    Update update = Update(&go);
    update.stuffs.push_back(model.getStuff());

    std::thread updateThread(&Update::updateModels, &update);

    graphicsThread.join();
    go = false;
    updateThread.join();
}
