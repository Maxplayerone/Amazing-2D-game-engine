#include<iostream>
#include<chrono>

//openGL
#include"GL/glew.h"
#include <GLFW/glfw3.h>

//GLM
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"glm/gtc/type_ptr.hpp"

//imGui
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

//utilities
#include"Utils/ErrorHandling.h"

//buffers
#include"Buffers/VertexBuffer.h"
#include"Buffers/VertexArray.h"
#include"Buffers/VertexBufferLayout.h"
#include"Buffers/IndexBuffer.h"

//shaders
#include"Shadering/Shader.h"
#include"Shadering/Renderer.h"
#include"Shadering/Texture.h"

#include"ECS/SpriteRenderer.h"
#include"ECS/Transform.h"
#include"ECS/Audio.h"  
#include"ECS/GameObject.h"
#include"ECS/SpriteSheet.h"

//camera
#include"Camera/Camera.h"
#include"Camera/ModelMatrix.h"
#include"Camera/ProjectionMatrix.h"
#include"Camera/ViewMatrix.h"

#define WIDTH 640
#define HEIGHT 480

GLFWwindow* Init(void);
void Shutdown(void);
void ChangeScene(int);
Scene::Scene* currentScene;

std::string engineName = "Hello world";

unsigned int masterID;
unsigned int GiveID() {
    return masterID++;
}

int main(void)
{
    GLFWwindow* window = Init();

    auto startTime = std::chrono::high_resolution_clock::now();
    std::chrono::steady_clock::time_point endTime;

    Renderer* rend = new Renderer();
    Shader shaderProgram("Assets/Shaders/Shader.shader");    

   ModelMatrix* _modelMatrix = new ModelMatrix();
   ViewMatrix* _viewMatrix = new ViewMatrix();
   ProjectionMatrix* _projectionMatrix = new ProjectionMatrix();

   Camera* camera = new Camera(shaderProgram);
   camera->Push(Camera::MatrixType::TYPE_MODEL, _modelMatrix->GetModelMatrix(), shaderProgram);
   camera->Push(Camera::MatrixType::TYPE_VIEW, _viewMatrix->GetViewMatrix(), shaderProgram);
   camera->Push(Camera::MatrixType::TYPE_PROJECTION, _projectionMatrix->GetProjectionMatrix(), shaderProgram);

    //textures (to be abstracted)

    Texture trollTexture("Assets/Images/trollface.png", 1);
    Texture amogusTexture("Assets/Images/amogus.jpg", 2);

    SpriteSheet* spriteSheet = new SpriteSheet(new Texture("Assets/Images/spritesheet.png", 3) , 16, 16, 26, 0);

    Sprite* testSprite = spriteSheet->GetSprite(9);

    shaderProgram.SetUniform1iv("u_Textures");

    GameObject* trollface = new GameObject(GiveID());
    trollface->AddComponent(new SpriteRenderer(1));
    trollface->AddComponent(new Transform(-0.5f, -0.5f));
    
    
    GameObject* amogus = new GameObject(GiveID());
    amogus->AddComponent(new SpriteRenderer(1));
    amogus->AddComponent(new Transform(1.0f, -1.0f));

    std::chrono::duration<float> deltaTime;

    float color[3] = { 0.0f, 0.0f, 0.0f};
    float modelScale = 1.0f;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    
    while (!glfwWindowShouldClose(window)) {    

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Testin");
        ImGui::SliderFloat("Camera zoom", &modelScale, 0.0f, 5.0f);
        ImGui::ColorEdit3("BG color", color);
        ImGui::End();

        rend->ChangeBGColor(color[0], color[1], color[2], 0.0f);
        rend->DrawSingle(trollface, shaderProgram);

        _projectionMatrix = new ProjectionMatrix(modelScale);
        camera->Push(Camera::MatrixType::TYPE_PROJECTION, _projectionMatrix->GetProjectionMatrix(), shaderProgram);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();

        //delta time
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
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    if (glewInit() != GLEW_OK)
        std::cout << "[GLEW ERROR] cannot initialize glew" << std::endl;

    return window;
}

//free's window and other stuff
void Shutdown(void) {
    KeyHandleler::Get().~KeyHandleler();
    MouseHandleler::Get().~MouseHandleler();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
}

/*
void ChangeScene(int sceneIndex) {
    switch (sceneIndex) {
    case 0:
        currentScene = new Scene::LevelScene();
        break;
    case 1:
        currentScene = new Scene::LevelEditorScene();
        break;
    default:
        std::cout << "Cannot load scene " << sceneIndex << std::endl;
    }
}
*/