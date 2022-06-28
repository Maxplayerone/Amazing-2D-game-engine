#include<iostream>
#include<chrono>

//openGL
#include"GL/glew.h"
#include <GLFW/glfw3.h>

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

#define WIDTH 640
#define HEIGHT 480

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
    
    Shader shaderProgram = AssetsPool::Get().GetShader("Assets/shaders/shader.shader");

    Camera* camera = new Camera(shaderProgram);
    camera->Push(Camera::MatrixType::TYPE_MODEL, _modelMatrix->GetModelMatrix(), shaderProgram);
    camera->Push(Camera::MatrixType::TYPE_VIEW, _viewMatrix->GetViewMatrix(), shaderProgram);
    camera->Push(Camera::MatrixType::TYPE_PROJECTION, _projectionMatrix->GetProjectionMatrix(), shaderProgram);

    ChangeScene(1);
    float scaleValue = 1.0f;
    while (!glfwWindowShouldClose(window)) {

        if (KeyHandleler::Get().IsKeyPressed(GLFW_KEY_U)) ChangeScene(1);
        if (KeyHandleler::Get().IsKeyPressed(GLFW_KEY_I)) ChangeScene(0);

        if (currentScene != nullptr)
          currentScene->OnUpdate(deltaTime.count());

        if (KeyHandleler::Get().IsKeyHeld(GLFW_KEY_Q)) {
            scaleValue += 0.05f;
            _projectionMatrix = new ProjectionMatrix(scaleValue);
            camera->Push(Camera::MatrixType::TYPE_PROJECTION, _projectionMatrix->GetProjectionMatrix(), shaderProgram);
        }
        if (KeyHandleler::Get().IsKeyHeld(GLFW_KEY_W)) {
            scaleValue -= 0.05f;
            _projectionMatrix = new ProjectionMatrix(scaleValue);
            camera->Push(Camera::MatrixType::TYPE_PROJECTION, _projectionMatrix->GetProjectionMatrix(), shaderProgram);
        }

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