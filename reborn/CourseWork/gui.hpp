#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <glm/glm.hpp>

#pragma execution_character_set("utf-8")


class Gui 
{
public:
    Gui(GLFWwindow* window, Loader& modelsLoader, Scene& scene, Shader& shader) : 
        modelsLoader(modelsLoader), 
        scene(scene),
        shader(shader),
        newObject(nullptr)
    {
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        ImGuiIO& io = ImGui::GetIO();
        io.Fonts->AddFontFromFileTTF("fonts/clear-sans.ttf", 18, NULL, io.Fonts->GetGlyphRangesCyrillic());

        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

        // Setup style
        ImGui::StyleColorsDark();

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 330");

        // Setup clear color
        ImVec4 clear_color = ImVec4(0.1f, 0.1f, 0.2f, 1.0f);

        shader.use();
        shader.setVec3("lightColor", glm::vec3(lightingColor[0], lightingColor[1], lightingColor[2]));
        shader.setVec3("lightPos", lightingPosition);
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
        ImGui::Text("Цвет препятствия");
        ImGui::ColorEdit3("", objectColor);

        ImGui::Text("Позиция");
        ImGui::SliderFloat("X##Позиция", &objectPosition.x, -8, 8);
        ImGui::SliderFloat("Y##Позиция", &objectPosition.y, -8, 8);
        ImGui::SliderFloat("Z##Позиция", &objectPosition.z, -8, 8);

        ImGui::Text("Масштаб");
        ImGui::SliderFloat("RX##Масштаб", &objectScale.x, 0.1, 3);
        ImGui::SliderFloat("RY##Масштаб", &objectScale.y, 0.1, 3);
        ImGui::SliderFloat("RZ##Масштаб", &objectScale.z, 0.1, 3);

        ImGui::Text("Угол поворота (в градусах)");
        ImGui::SliderAngle("SX##Поворот", &objectRotation.x, 0, 360);
        ImGui::SliderAngle("SY##Поворот", &objectRotation.y, 0, 360);
        ImGui::SliderAngle("SZ##Поворот", &objectRotation.z, 0, 360);

        if (ImGui::Button("Разместить препятствие", ImVec2(300, 40)))
        {
            glm::mat4 modelMatrix = glm::mat4(1.0f);

            modelMatrix = glm::rotate(modelMatrix, objectRotation.x, glm::vec3(1, 0, 0));
            modelMatrix = glm::rotate(modelMatrix, objectRotation.y, glm::vec3(0, 1, 0));
            modelMatrix = glm::rotate(modelMatrix, objectRotation.z, glm::vec3(0, 0, 1));

            modelMatrix = glm::scale(modelMatrix, objectScale);

            modelMatrix = glm::translate(modelMatrix, objectPosition);

            glm::vec4 modelColor = glm::vec4(objectColor[0], objectColor[1], objectColor[2], 1);

            newObject = new Obstacle(modelMatrix, modelColor, GL_BACK);
            modelsLoader.loadModel(cubeModel, *newObject);
            scene.addObject(newObject);
            ++modelsCount;
        }

        if (!showDeleteMenu && ImGui::Button("Удалить препятствие", ImVec2(300, 40)) && modelsCount > 0)
                showDeleteMenu = true;
        else if (showDeleteMenu)
        {
            static int deletedModelNum = 1;
            static int prevDeletedModelIndex = -1;
            static int deletedModelIndex = deletedModelNum - 1;
            static glm::vec4 lastColor = scene.getObjectColor(deletedModelIndex);;

            ImGui::Text("Выберите препятствие для удаления:");
            ImGui::SetNextItemWidth(300);
            ImGui::SliderInt("", &deletedModelNum, 1, modelsCount);

            deletedModelIndex = deletedModelNum - 1;

            if (prevDeletedModelIndex != deletedModelIndex)
             {
                if (prevDeletedModelIndex != -1)
                    scene.updateObjectColor(lastColor, prevDeletedModelIndex);
                prevDeletedModelIndex = deletedModelIndex;
                lastColor = scene.getObjectColor(deletedModelIndex);
                scene.updateObjectColor(deletedObjectColor, deletedModelIndex);
            }

            if (ImGui::Button("Подтвердить удаление", ImVec2(300, 40)))
                if (deletedModelIndex >= 0 && deletedModelIndex < modelsCount)
                {
                    scene.removeObject(deletedModelIndex);
                    showDeleteMenu = false;
                    deletedModelNum = 1;
                    prevDeletedModelIndex = -1;
                    --modelsCount;
                }
            if (ImGui::Button("Отмена", ImVec2(300, 40)))
            {
                scene.updateObjectColor(lastColor, deletedModelIndex);
                showDeleteMenu = false;
                deletedModelNum = 1;
                prevDeletedModelIndex = -1;
            }
        }
    }

    void RenderLightingMenu()
    {
        ImGui::Text("Цвет источника света");
        ImGui::ColorEdit3("", lightingColor);

        ImGui::Text("Позиция");
        ImGui::SliderFloat("X##Позиция", &lightingPosition.x, -100, 100);
        ImGui::SliderFloat("Y##Позиция", &lightingPosition.y, -100, 100);
        ImGui::SliderFloat("Z##Позиция", &lightingPosition.z, -100, 100);

        if (ImGui::Button("Установить источник света", ImVec2(300, 40)))
        {
            shader.use();
            shader.setVec3("lightColor", glm::vec3(lightingColor[0], lightingColor[1], lightingColor[2]));
            shader.setVec3("lightPos", lightingPosition);
        }
        if (ImGui::Button("Удалить источник света", ImVec2(300, 40)))
        {
            shader.use();
            shader.setVec3("lightColor", glm::vec3(0, 0, 0));
        }
    }

    void RenderWaveSourceMenu()
    {
        ImGui::Text("Позиция");
        ImGui::SliderFloat("X##Позиция", &waveSourcePosition.x, -8, 8);
        ImGui::SliderFloat("Y##Позиция", &waveSourcePosition.y, -8, 8);
        ImGui::SliderFloat("Z##Позиция", &waveSourcePosition.z, -8, 8);

        ImGui::Text("Скорость распространения волны");
        ImGui::SliderFloat("S##", &waveSpeed, 0, 100);

        if (ImGui::Button("Установить источник звуковых волн", ImVec2(300, 40)))
        {
            glm::mat4 waveMatrix = glm::mat4(1.0f);

            waveMatrix = glm::translate(waveMatrix, waveSourcePosition);

            glm::vec4 newWaveColor = glm::vec4(waveColor[0], waveColor[1], waveColor[2], 0.1);

            newObject = new Sphere(waveMatrix, newWaveColor, waveSpeed);
            modelsLoader.loadModel(sphereModel, *newObject);
            waves.push_back(newObject);
        }

        if (ImGui::Button("Испустить волну из источников звука", ImVec2(300, 40)))
            for (auto& wave : waves)
                scene.addSphere(new Sphere(*wave));

        if (!showDeleteMenu && ImGui::Button("Удалить источник звука", ImVec2(300, 40)) && waves.size() > 0)
            showDeleteMenu = true;
        else if (showDeleteMenu)
        {
            static int deletedWaveSourceNum = 1;

            ImGui::Text("Выберите номер источника звука для удаления:");
            ImGui::SetNextItemWidth(300);
            ImGui::SliderInt("", &deletedWaveSourceNum, 1, waves.size());

            if (ImGui::Button("Подтвердить удаление", ImVec2(300, 40)))
                if (deletedWaveSourceNum - 1 >= 0 && deletedWaveSourceNum - 1 < waves.size())
                {
                    waves.erase(waves.begin() + deletedWaveSourceNum - 1);
                    showDeleteMenu = false;
                }
            if (ImGui::Button("Отмена", ImVec2(300, 40)))
                showDeleteMenu = false;
        }
    }

    void RenderUI()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Главное меню");

        RenderStyle();

        if (ImGui::CollapsingHeader("Препятствия"))
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

        if (ImGui::CollapsingHeader("Источник звука"))
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
    const char* sphereModel = "models/sphere_big.obj";

    Scene& scene;
    Loader& modelsLoader;
    Shader& shader;

    Model* newObject;
    int modelsCount = 0;

    float objectColor[3] = { 0.2f, 0.3f, 0.4f };
    glm::vec4 deletedObjectColor = glm::vec4(1, 0, 0, 1);
    glm::vec3 objectPosition = glm::vec3(0.0f);
    glm::vec3 objectScale = glm::vec3(1.0f);
    glm::vec3 objectRotation = glm::vec3(0.0f);

    float lightingColor[3] = { 1.0f, 1.0f, 1.0f };
    glm::vec3 lightingPosition = glm::vec3(100.0f, 0.0f, -70.0f);

    float waveColor[3] = { 1, 1, 1 };
    glm::vec3 waveSourcePosition = glm::vec3(0.0f, 0.0f, 0.0f);
    float waveSpeed = 1.0f;
    std::vector<Model*> waves;

    bool showObstacleMenu = false;
    bool showLightingMenu = false;
    bool showWaveSourceMenu = false;
    bool showDeleteMenu = false;
};
