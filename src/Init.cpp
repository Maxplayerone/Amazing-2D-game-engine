#include<iostream>
#include<chrono>

//openGL
#include"GL/glew.h"
#include <GLFW/glfw3.h>

//I am a gui
#include"yoinked libs/imGui/imgui.h"
#include"yoinked libs/imGui/imgui_impl_glfw.h"
#include"yoinked libs/imGui/imgui_impl_opengl3.h"

//input
#include"InputHandling/InputCallbacks.h"
#include"InputHandling/KeysHandleler.h"
#include"InputHandling/MouseHandleler.h"

//scene managment
#include"SceneManagment/LevelEditorScene.h"
#include"SceneManagment/LevelScene.h"

//shaders
#include"Shadering/Shader.h"

//camera
#include"Camera/Camera.h"
#include"Camera/ModelMatrix.h"
#include"Camera/ProjectionMatrix.h"
#include"Camera/ViewMatrix.h"

#include"Utils/AssetsPool.h"

#define WIDTH 960
#define HEIGHT 720

GLFWwindow* Init(void);
void Shutdown(void);
void ChangeScene(int);
Scene* currentScene;

std::string engineName = "Hello world";

unsigned int masterID = 0;
unsigned int GiveID() {
    return masterID++;
}

int main(void)
{
    GLFWwindow* window = Init();

    auto startTime = std::chrono::high_resolution_clock::now();
    std::chrono::steady_clock::time_point endTime;
    std::chrono::duration<float> deltaTime;
    
    ModelMatrix* _modelMatrix = new ModelMatrix();
    ViewMatrix* _viewMatrix = new ViewMatrix();
    ProjectionMatrix* _projectionMatrix = new ProjectionMatrix();
    
    Shader* shaderProgram = AssetsPool::Get().GetShader("Assets/shaders/shader.shader");

    Camera* camera = new Camera(*shaderProgram);
    camera->Push(Camera::MatrixType::TYPE_MODEL, _modelMatrix->GetModelMatrix(), *shaderProgram);
    camera->Push(Camera::MatrixType::TYPE_VIEW, _viewMatrix->GetViewMatrix(), *shaderProgram);
    camera->Push(Camera::MatrixType::TYPE_PROJECTION, _projectionMatrix->GetProjectionMatrix(), *shaderProgram);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    ChangeScene(1);
    float scaleValue = 3.5f;
    float nothing = 0.0f;

    while (!glfwWindowShouldClose(window)) {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (KeyHandleler::Get().IsKeyPressed(GLFW_KEY_U)) ChangeScene(1);
        if (KeyHandleler::Get().IsKeyPressed(GLFW_KEY_I)) ChangeScene(0);

        if (currentScene != nullptr) {
            currentScene->OnUpdate(deltaTime.count());
            currentScene->ImGui();
        }

        ImGui::Begin("window");
        ImGui::SliderFloat("Camera zoom", &scaleValue, 0.0f, 5.0f);
        ImGui::End();


        //works just fine
        /*
        ImGui::Begin("Another test");
        ImGui::SliderFloat("Nothing", &nothing, 0.0f, 100.0f);
        ImGui::End();
        */
        _projectionMatrix = new ProjectionMatrix(scaleValue);
        camera->Push(Camera::MatrixType::TYPE_PROJECTION, _projectionMatrix->GetProjectionMatrix(), *shaderProgram);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
        glfwPollEvents();

        endTime = std::chrono::high_resolution_clock::now();
        deltaTime = endTime - startTime;
        startTime = endTime;
    }

    Shutdown();
    return 0;
}

//initliazes glfw window and glew
GLFWwindow* Init(void) {
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        exit(1);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(WIDTH, HEIGHT, engineName.c_str(), NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(1);
    }
    //callbacks for the mouse and keyboard input
    glfwSetKeyCallback(window, KeyCallBack);
    glfwSetMouseButtonCallback(window, MouseButtonCallback);
    glfwSetScrollCallback(window, ScrollCallback);
    glfwSetCursorPosCallback(window, CursorPosCallback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glViewport(0, 0, WIDTH, HEIGHT);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if (glewInit() != GLEW_OK)
        std::cout << "[GLEW ERROR] cannot initialize glew" << std::endl;

    return window;
}

//free's window and other stuff
void Shutdown(void) {
    //KeyHandleler::Get().~KeyHandleler();
    //MouseHandleler::Get().~MouseHandleler();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
}


void ChangeScene(int sceneIndex) {
    switch (sceneIndex) {
    case 0:
        currentScene = new LevelScene();
        break;
    case 1:
        currentScene = new LevelEditorScene();
        break;
    default:
        std::cout << "Cannot load scene " << sceneIndex << std::endl;
    }
}