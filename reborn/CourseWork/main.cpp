#include "loader.hpp"
#include "camera.hpp"
#include "scene.hpp"
#include "sphere.hpp"
#include "obstacle.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void processInput(GLFWwindow* window);

/**
 * \brief Window width
 */
const unsigned int SCR_WIDTH = 900;
/**
 * \brief Window height
 */
const unsigned int SCR_HEIGHT = 900;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

bool ctrlPressed = false;
bool cursorVisible = false;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// ImGui window show
bool showWindow = true;

// lighting
glm::vec3 lightPos(10, 50, 10);


float color[3] = { 1.0f, 1.0f, 1.0f };
glm::vec3 objectPosition(0.0f);
glm::vec3 objectScale(1.0f);
glm::vec3 objectRotation(0.0f);


int main()
{
    // Init glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Course work", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetKeyCallback(window, key_callback);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init("#version 330");

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Load glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return EXIT_FAILURE;
    }

    // Create shaders
    Shader shader("shaders/shader.vert", "shaders/shader.frag");

    // Create model loader
    Loader modelLoader;

    // Create models
    glm::mat4 mSphere = glm::mat4(1);
    mSphere = glm::translate(mSphere, glm::vec3(0, 0, -6.5));
    glm::vec4 sphereColor(1, 1, 1, 0.8);
    Sphere sphere(mSphere, sphereColor);
    modelLoader.loadModel("models/sphere.obj", sphere);

    glm::mat4 mRoom = glm::mat4(1.0f);
    mRoom = glm::scale(mRoom, glm::vec3(20, 20, 20));
    glm::vec4 roomColor(1.0f, 0.5f, 0.31f, 0.3f);
    Obstacle room(mRoom, roomColor, GL_FRONT, false);
    modelLoader.loadModel("models/room.obj", room);

    glm::mat4 mObst = glm::mat4(1.0f);
    mObst = glm::rotate(mObst, glm::radians(20.0f), glm::vec3(0, 1, 0));
    glm::vec4 obstColor(0.2, 0.2, 0.2, 1);
    Obstacle obst(mObst, obstColor, GL_BACK);
    modelLoader.loadModel("models/cube.obj", obst);

    // Create scene
    Scene scene;
    scene.addObject(obst);

    glEnable(GL_DEPTH_TEST);

    float angle = 0;

    
    Obstacle* newObst;

    // Event loop
    while (!glfwWindowShouldClose(window))
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (showWindow)
        {
            ImGui::Begin("Object Placement", nullptr, ImGuiWindowFlags_NoCollapse);

            ImGui::Text("Select color for new model: ");
            ImGui::ColorEdit3("RGB Color", color);

            ImGui::Text("New object position");
            ImGui::SliderFloat("X##Position", &objectPosition.x, -8, 8);
            ImGui::SliderFloat("Y##Position", &objectPosition.y, -8, 8);
            ImGui::SliderFloat("Z##Position", &objectPosition.z, -8, 8);

            // Input fields for object scale
            ImGui::Text("Object Scale");
            ImGui::SliderFloat("X##Scale", &objectScale.x, 0.1, 3);
            ImGui::SliderFloat("Y##Scale", &objectScale.y, 0.1, 3);
            ImGui::SliderFloat("Z##Scale", &objectScale.z, 0.1, 3);

            // Input fields for object rotation
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

                //Obstacle newObst(modelMatrix, modelColor, GL_FRONT);
                newObst = new Obstacle(modelMatrix, modelColor, GL_FRONT);
                modelLoader.loadModel("models/cube.obj", *newObst);
                scene.addObject(*newObst);
            }

            // Удаление
            //ImGui::Combo("##objectcombo", &selectedObjectIndex, objectList, IM_ARRAYSIZE(objectList));

            ImGui::End();
        }

        glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        shader.use();
        shader.setVec3("lightPos", lightPos);
        shader.setVec3("viewPos", camera.Position);

        glm::mat4 proj = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();

        shader.setMat4("proj", proj);
        shader.setMat4("view", view);

        float glTime = glfwGetTime();

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_CULL_FACE);
        room.Draw(shader, glTime, scene);
        glDisable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glDisable(GL_CULL_FACE);
        scene.render(shader, glTime);
        sphere.Draw(shader, glTime, scene);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();

    return EXIT_SUCCESS;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    if (cursorVisible) {
        return;
    }
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_LEFT_CONTROL)
    {
        if (action == GLFW_PRESS)
        {
            ctrlPressed = true;
            cursorVisible = !cursorVisible; // Инвертируем состояние видимости курсора
            if (cursorVisible)
            {
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); // Показать курсор
            }
            else
            {
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // Спрятать курсор
            }
        }
    }

    if (key == GLFW_KEY_1 && action == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else if (key == GLFW_KEY_2 && action == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}