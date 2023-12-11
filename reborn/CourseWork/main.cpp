#include "shader.hpp"
#include "scene.hpp"
#include "model.hpp"

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

// camera
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

bool firstMouse = true;
float yaw = -90.0f;
float pitch = 0.0f;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;
float fov = 45.0f;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// ImGui window show
bool showWindow = true;

/**
 * \brief Window width
 */
const unsigned int SCR_WIDTH = 900;
/**
 * \brief Window height
 */
const unsigned int SCR_HEIGHT = 900;

//ImGui::Begin("Objects");
////ImGui::SliderFloat("Angle X", &angle[0], 0.0f, 360.0f);
////ImGui::SliderFloat("Angle Y", &angle[1], 0.0f, 360.0f);
////ImGui::SliderFloat("Angle Z", &angle[2], 0.0f, 360.0f);
////ImGui::SliderFloat("Light X", &lightPos.x, -5.0f, 5.0f);
//ImGui::SliderFloat("Light Power", &lightPos.y, -20.0f, 105.0f);
////ImGui::SliderFloat("Light Z", &lightPos.z, -5.0f, 5.0f);
//bool change = nigmode;
//ImGui::Checkbox("Nigmode", &nigmode);
//change = nigmode != change;
//// if(change)
//// {
////     char str1[] = "./tex/container2.png";
////     char str2[] = "./tex/prikol2.png";
////     char *str = nigmode ? str2 : str1;
////     data = stbi_load(str, &width, &height, &nrChannels, 0);
////     glGenTextures(1, &texture3);
////     glBindTexture(GL_TEXTURE_2D, texture3);
////     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
////     stbi_image_free(data);
////     glGenerateMipmap(GL_TEXTURE_2D);
////     glBindTexture(GL_TEXTURE_2D, texture3);   
//// }
//
//ImGui::End();
//ImGui::Begin("Camera");
//ImGui::SliderFloat("FoV", &fov, 0.0f, 180.0f);
//ImGui::LabelText("Camera X", "%f", cam.pos.x);
//ImGui::LabelText("Camera Y", "%f", cam.pos.y);
//ImGui::LabelText("Camera Z", "%f", cam.pos.z);
//
//ImGui::End();


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
    Shader shaders("shaders/shader.vert", "shaders/shader.frag");

    // Create scene
    Scene scene;

    Model sphere("models/icosphere.obj");
    glm::vec3 sphereColor = glm::vec3(0.0f);
    Model room("models/cube.obj");
    scene.addObject(room);

    Model cube("models/cube.obj");
    sphere.addObject(cube);

    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_FRONT);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetKeyCallback(window, key_callback);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Event loop
    while (!glfwWindowShouldClose(window))
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (showWindow)
        {
            ImGui::Begin("Menu", &showWindow);
            //ImGui::Text("!");
            ImGui::SliderFloat3("Sphere color (R, G, B)", (float *)(&sphereColor), 0.0f, 1.0f);
            ImGui::End();
        }

        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClearColor(1, 1, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaders.use();
        glm::mat4 proj = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        shaders.setMat4("proj", proj);
        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        shaders.setMat4("view", view);

        shaders.setVec4("figureColor", glm::vec4(0, 0, 0, 0.4));
        glm::mat4 m = glm::mat4(1.0f);
        shaders.setMat4("model", m);

        //room.Draw(shaders);

        m = glm::scale(m, glm::vec3(0.2, 0.2, 0.2));
        m = glm::rotate(m, glm::radians(20.0f), glm::vec3(0, 1, 0));
        shaders.setMat4("model", m);
        shaders.setVec4("figureColor", glm::vec4(0.3, 0.3, 0.3, 1));

        cube.Draw(shaders);

        float u_time = glfwGetTime();
        m = glm::rotate(m, glm::radians(-20.0f), glm::vec3(0, 1, 0));
        m = glm::translate(m, glm::vec3(0, 0, -2.5));
        shaders.setMat4("model", m);
        shaders.setVec4("figureColor", glm::vec4(sphereColor, 0.4));

        sphere.Draw(shaders, true);

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

    float cameraSpeed = static_cast<float>(3 * deltaTime);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.085f; // change this value to your liking
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_LEFT_CONTROL && action == GLFW_PRESS)
    {
        int mouse_enabled = glfwGetInputMode(window, GLFW_CURSOR);

        if (mouse_enabled == GLFW_CURSOR_NORMAL)
        {
            glfwSetCursorPosCallback(window, mouse_callback);
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
        else
        {
            glfwSetCursorPosCallback(window, ImGui_ImplGlfw_CursorPosCallback);
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            glfwSetCursorPos(window, SCR_WIDTH / 2, SCR_HEIGHT / 2);
        }
    }
}
