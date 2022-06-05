#include<iostream>
#include<chrono>

//openGL
#include"GL/glew.h"
#include <GLFW/glfw3.h>

//GLM
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"glm/gtc/type_ptr.hpp"

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

#define WIDTH 640
#define HEIGHT 480

GLFWwindow* Init(void);
void Shutdown(void);
void ChangeScene(int);
Scene::Scene* currentScene;

int main(void)
{
    GLFWwindow* window = Init();

    auto startTime = std::chrono::high_resolution_clock::now();
    std::chrono::steady_clock::time_point endTime;

    float vertices[] = {
               //position        color       texture
             -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,// bottom-left
              0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,// bottom-right
              0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,// top-right
             -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f// top-left
    };

    unsigned int indices[] = {
    //bottom-left, bottom-right, top-right
     //top-right, top-left, bottom-left
      0, 1, 2,
      2, 3, 0
    };

    VertexArray vertexArray;
    VertexBuffer vertexBuffer(sizeof(vertices), vertices);

    VertexBufferLayout vertexBufferLayout;
    vertexBufferLayout.AddFloat(2); //position vertex
    vertexBufferLayout.AddFloat(3); //color vertex
    vertexBufferLayout.AddFloat(2); //texture vertex
    vertexArray.AddVertexBuffer(vertexBuffer, vertexBufferLayout);

    unsigned int indeciesCount = 6;
    IndexBuffer indexBuffer(indeciesCount, indices);
    
    Shader shaderProgram("Assets/Shaders/Shader.shader");
    Renderer rend;

    glm::mat4 modelMat = glm::mat4(1.0f); //identity matrix
    modelMat = glm::rotate(modelMat, glm::radians(-55.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    modelMat = glm::scale(modelMat, glm::vec3(0.5f, 0.5f, 0.5f));

    glm::mat4 viewMat = glm::mat4(1.0f);

    glm::mat4 projMat = glm::mat4(1.0f);
    projMat = glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f, -1.0f, 1.0f);

    shaderProgram.SetUniformMat4f("model", modelMat);
    shaderProgram.SetUniformMat4f("view", viewMat); 
    shaderProgram.SetUniformMat4f("projection", projMat);

    Texture texture("Assets/Images/trollface.png");
    texture.Bind();
    shaderProgram.SetUniform1i("fTexture", 0);

    std::chrono::duration<float> deltaTime;

    
    SpriteRenderer* spriteRend = new SpriteRenderer("SpriteRend");
    Transform* transform = new Transform("Transform");
    Audio* audio = new Audio("Audio");

    GameObject Bjorne;

    Bjorne.AddComponent(spriteRend);
    Bjorne.AddComponent(audio);
    Bjorne.AddComponent(transform);

    spriteRend->value = 192;

    SpriteRenderer* newSr = Bjorne.RemoveComponent<SpriteRenderer>();
    std::cout << newSr->value << std::endl;

    float r = 0.0f;
    /*
    while (!glfwWindowShouldClose(window)) {

       rend.ChangeBGColor(0.0f, 0.0f, 0.0f, 0.0f);
       rend.Draw(vertexArray, indexBuffer, shaderProgram);

        if (MouseHandleler::Get().IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
           // ChangeScene(0);
        if (MouseHandleler::Get().IsMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT))
            //ChangeScene(1);

        if (currentScene != nullptr)
            currentScene->OnUpdate(deltaTime.count(), r);

        glfwSwapBuffers(window);
        glfwPollEvents();

        //delta time
        endTime = std::chrono::high_resolution_clock::now();
        deltaTime = endTime - startTime;
        startTime = endTime;
    }
    */
    //this triggers an error for some reason
    //Shutdown();
    return 0;
}

//initliazes glfw window and glew
GLFWwindow* Init(void) {
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        exit(1);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(WIDTH, HEIGHT, "Hello World", NULL, NULL);
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

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        std::cout << "[GLEW ERROR] cannot initialize glew" << std::endl;

    return window;
}

//free's window and other stuff
void Shutdown(void) {
    KeyHandleler::Get().~KeyHandleler();
    MouseHandleler::Get().~MouseHandleler();
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