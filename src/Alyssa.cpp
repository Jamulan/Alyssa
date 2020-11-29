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

#define WIDTH 1600
#define HEIGHT 900

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
            int modifer = -1;
            for(LocOri* stuff : stuffs) {
                stuff->angle = 30.0f * t * modifer;
                modifer *= -1;
            }
        }
    }

    GLFWwindow *window;
    Application *application;
    double xLook, yLook;
    void updateView() {
        double xpos = 0, ypos = 0;
        double xLast, yLast, xDiff, yDiff;
        while(*go) {
            xLast = xpos; yLast = ypos;
            glfwGetCursorPos(window, &xpos, &ypos);
            xpos = (xpos - WIDTH)/6.0f;
            ypos = (ypos - HEIGHT)/-6.0f;

            xDiff = xpos - xLast;
            yDiff = ypos - yLast;

            xLook += xDiff;
            yDiff + yLook < 0 && yDiff + yLook > -180 ? yLook += yDiff : yLook += 0;
            application->setView(xLook, yLook, 60.0f);
        }
    }
};

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Alyssa-Demo", nullptr, nullptr);
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
            .pos = glm::vec3(1.0f, 2.0f, 0.0f),
            .rot = glm::vec3(0.0f, 0.0f, 1.0f),
            .angle = 0.0f,
            .sca = glm::vec3(0.5f)
    };
    ModelInfo modelInfo = {
            .stuff = stuff
    };
    LocOri stuff1 = stuff;
    stuff1.pos = glm::vec3(-1.0f, 2.0f, 0.0f);
    ModelInfo modelInfo1 = {
            .stuff = stuff1
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
    Model model1 = Model(&material, "assets/textures/Dodecahedron.png", "assets/models/Dodecahedron.obj", modelInfo1);

    app.setView(0, 0, 0);

    std::thread graphicsThread(&Application::run, &app);

    bool go = true;

    Update update = Update(&go, window, &app);
    update.stuffs.push_back(model.getStuff());
    update.stuffs.push_back(model1.getStuff());

    std::thread updateModelsThread(&Update::updateModels, &update);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    std::thread updateViewThread(&Update::updateView, &update);

    graphicsThread.join();
    go = false;
    updateViewThread.join();
    updateModelsThread.join();
}
