//
// Created by jamulan on 2020-11-11.
//

#include <cstdio>
#include <thread>
#include "Engine/Core.h"
#include "Engine/Application.h"
#include "Engine/Material.h"
#include "Engine/Model.h"

#define GLM_FOCE_RADIANS

static auto startTime = std::chrono::high_resolution_clock::now();

class Update {
public:
    Update(bool *go, GLFWwindow *window, Application *application) : go(go), window(window), application(application) {
        stuffs = {};
    }

    std::vector<LocOri*> stuffs;
    bool *go;
    void updateModels() {
        while(*go) {
            float t = std::chrono::duration<float, std::chrono::seconds::period>(
                    std::chrono::high_resolution_clock::now() - startTime).count();
            for(LocOri* stuff : stuffs) {
                stuff->angle = 30.0f * t;
            }
        }
    }

    GLFWwindow *window;
    Application *application;
    void updateView() {
        double xpos, ypos;
        while(*go) {
            glfwGetCursorPos(window, &xpos, &ypos);
            application->setView((xpos-1600.0f)/4.0f, ((ypos-900.0f)/-4.0f) - 100.0f);
        }
    }
};

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    GLFWwindow *window = glfwCreateWindow(1600, 900, "Alyssa-Demo", nullptr, nullptr);
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
            .pos = glm::vec3(2.0f, 2.0f, 0.0f),
            .rot = glm::vec3(0.0f, 0.0f, 1.0f),
            .angle = 0.0f,
            .sca = glm::vec3(0.5f)
    };
    ModelInfo modelInfo = {
            .stuff = stuff
    };
    LocOri stuff0 = {
            .pos = glm::vec3(0.0f, 0.0f, 6.0f),
            .rot = glm::vec3(1.0f, 0.0f, 0.0f),
            .angle = 90.0f,
            .sca = glm::vec3(1.0f)
    };
    ModelInfo modelInfo0 = {
            .stuff = stuff0
    };
    Model model0 = Model(&material, "assets/textures/tmpFloor.png", "assets/models/tmpFloor.obj", modelInfo0);
    Model model = Model(&material, "assets/textures/Dodecahedron.png", "assets/models/Dodecahedron.obj", modelInfo);

    app.setView(0, 0);

    std::thread graphicsThread(&Application::run, &app);

    bool go = true;

    Update update = Update(&go, window, &app);
    update.stuffs.push_back(model.getStuff());

    std::thread updateModelsThread(&Update::updateModels, &update);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    std::thread updateViewThread(&Update::updateView, &update);

    graphicsThread.join();
    go = false;
    updateViewThread.join();
    updateModelsThread.join();
}
