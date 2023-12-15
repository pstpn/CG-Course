#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <glm/glm.hpp>

#pragma execution_character_set("utf-8")


class Gui 
{
public:
    Gui(GLFWwindow* window, Loader& modelsLoader, Scene& scene) : 
        modelsLoader(modelsLoader), 
        scene(scene),
        newModel(nullptr)
    {
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        ImGuiIO& io = ImGui::GetIO();
        io.Fonts->AddFontFromFileTTF("fonts/clear-sans.ttf", 15, NULL, io.Fonts->GetGlyphRangesCyrillic());

        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

        // Setup style
        ImGui::StyleColorsDark();

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 330");

        // Setup clear color
        ImVec4 clear_color = ImVec4(0.1f, 0.1f, 0.2f, 1.0f);
    }

    ~Gui()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void RenderStyle()
    {
        ImGuiStyle& style = ImGui::GetStyle();

        ImVec4* colors = style.Colors;
        colors[ImGuiCol_Text] = ImVec4(0.8f, 0.8f, 1.0f, 1.0f);
        colors[ImGuiCol_TextDisabled] = ImVec4(0.4f, 0.4f, 0.5f, 1.0f);
        colors[ImGuiCol_WindowBg] = ImVec4(0.1f, 0.1f, 0.2f, 0.4f);
        colors[ImGuiCol_ChildBg] = ImVec4(0.1f, 0.1f, 0.2f, 0.7f);
        colors[ImGuiCol_PopupBg] = ImVec4(0.1f, 0.1f, 0.2f, 0.9f);
        colors[ImGuiCol_Border] = ImVec4(0.8f, 0.8f, 1.0f, 0.0f);
        colors[ImGuiCol_BorderShadow] = ImVec4(0.8f, 0.8f, 1.0f, 0.0f);
        colors[ImGuiCol_FrameBg] = ImVec4(0.2f, 0.2f, 0.4f, 0.6f);

        style.FrameRounding = 13.0f;
        style.FramePadding = ImVec2(6.0f, 4.0f);
    }

    void RenderObstacleMenu() 
    {
        ImGui::Text("Obstacle Menu");

        ImGui::ColorEdit3("New model color", color);

        ImGui::Text("Привет");
        ImGui::SliderFloat("X##Position", &objectPosition.x, -8, 8);
        ImGui::SliderFloat("Y##Position", &objectPosition.y, -8, 8);
        ImGui::SliderFloat("Z##Position", &objectPosition.z, -8, 8);

        ImGui::Text("Object Scale");
        ImGui::SliderFloat("X##Scale", &objectScale.x, 0.1, 3);
        ImGui::SliderFloat("Y##Scale", &objectScale.y, 0.1, 3);
        ImGui::SliderFloat("Z##Scale", &objectScale.z, 0.1, 3);

        ImGui::Text("Object Rotation (in degrees)");
        ImGui::SliderAngle("X##Rotation", &objectRotation.x, 0, 360);
        ImGui::SliderAngle("Y##Rotation", &objectRotation.y, 0, 360);
        ImGui::SliderAngle("Z##Rotation", &objectRotation.z, 0, 360);

        if (ImGui::Button("Place Model", ImVec2(100, 40)))
        {
            glm::mat4 modelMatrix = glm::mat4(1);

            modelMatrix = glm::rotate(modelMatrix, objectRotation.x, glm::vec3(1, 0, 0));
            modelMatrix = glm::rotate(modelMatrix, objectRotation.y, glm::vec3(0, 1, 0));
            modelMatrix = glm::rotate(modelMatrix, objectRotation.z, glm::vec3(0, 0, 1));

            modelMatrix = glm::scale(modelMatrix, objectScale);

            modelMatrix = glm::translate(modelMatrix, objectPosition);

            glm::vec4 modelColor = glm::vec4(color[0], color[1], color[2], 1);

            newModel = new Obstacle(modelMatrix, modelColor, GL_FRONT);
            modelsLoader.loadModel(cubeModel, *newModel);
            scene.addObject(newModel);

            modelNames.push_back((std::string("Model ") + std::to_string(++modelsCount)).c_str());
        }

        if (ImGui::Button("Delete Model", ImVec2(100, 40)) && modelsCount > 0)
        {
            int deletedModel;

            ImGui::ListBox("##objectcombo", &deletedModel, &modelNames[0], IM_ARRAYSIZE(&modelNames[0]));

            --modelsCount;
        }
    }

    void RenderLightingMenu()
    {
        ImGui::Text("Lighting Menu");
    }

    void RenderWaveSourceMenu()
    {
        ImGui::Text("Wave Source Menu");
    }

    void RenderUI()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Main Menu");

        RenderStyle();

        if (ImGui::CollapsingHeader("Obstacles"))
        {
            showObstacleMenu = true;
            showLightingMenu = false;
            showWaveSourceMenu = false;
        }
        else
            showObstacleMenu = false;

        if (ImGui::CollapsingHeader("Освещение"))
        {
            showLightingMenu = true;
            showObstacleMenu = false;
            showWaveSourceMenu = false;
        }
        else
            showLightingMenu = false;

        if (ImGui::CollapsingHeader("Wave Source"))
        {
            showWaveSourceMenu = true;
            showObstacleMenu = false;
            showLightingMenu = false;
        }
        else
            showWaveSourceMenu = false;

        if (showObstacleMenu)
            RenderObstacleMenu();

        if (showLightingMenu)
            RenderLightingMenu();

        if (showWaveSourceMenu)
            RenderWaveSourceMenu();

        ImGui::End();
    }

    void EndRenderUI()
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

private:
    const char* cubeModel = "models/cube.obj";

    Scene& scene;
    Loader& modelsLoader;

    Model* newModel;
    int modelsCount = 0;
    std::vector<const char*> modelNames;

    float color[3] = { 0.2f, 0.3f, 0.4f };

    glm::vec3 objectPosition = glm::vec3(0.0f);
    glm::vec3 objectScale = glm::vec3(1.0f);
    glm::vec3 objectRotation = glm::vec3(0.0f);

    bool showObstacleMenu = false;
    bool showLightingMenu = false;
    bool showWaveSourceMenu = false;
};
