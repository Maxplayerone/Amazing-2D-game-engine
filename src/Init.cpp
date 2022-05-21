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

#define WIDTH 640
#define HEIGHT 480

GLFWwindow* Init(void);
void Shutdown(void);
void ChangeScene(int);
Scene::Scene* currentScene;

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float fov = 45.0f;

int main(void)
{
    GLFWwindow* window = Init();

    auto startTime = std::chrono::high_resolution_clock::now();
    std::chrono::steady_clock::time_point endTime;

    /*
    float vertices[] = {
             -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,// bottom-left
              0.5f, -0.5f, 1.0f, 0.0f, 0.0f,// bottom-right
              0.5f,  0.5f, 0.0f, 0.0f, 1.0f,// top-right
             -0.5f,  0.5f, 0.0f, 0.0f, 1.0f// top-left
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
    vertexArray.AddVertexBuffer(vertexBuffer, vertexBufferLayout);

    unsigned int indeciesCount = 6;
    IndexBuffer indexBuffer(indeciesCount, indices);
    */
    Shader shaderProgram("Assets/Shaders/Shader.shader");
    Renderer rend;

    GLCall(glEnable(GL_DEPTH_TEST));
    float verticesCube[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    
    unsigned int vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesCube), verticesCube, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glm::mat4 modelMat = glm::mat4(1.0f); //identity matrix
    modelMat = glm::rotate(modelMat, glm::radians(-55.0f), glm::vec3(0.5f, 1.0f, 0.0f));
    modelMat = glm::scale(modelMat, glm::vec3(0.5f, 0.5f, 0.5f));

    //glm::mat4 viewMat = glm::mat4(1.0f);
    //viewMat = glm::translate(viewMat, glm::vec3(0.0f, 0.0f, -3.0f)); //the camera moves to the back

    shaderProgram.SetUniformMat4f("model", modelMat);
    //shaderProgram.SetUniformMat4f("view", viewMat); 

    //delta time is an amount of time that it takes to finish a frame in a second
    //so if the game runs at 60 frames then it takes 0.016 seconds to run a frame (delta time)
    //and if the game runs at 30 frames delta is 0.032
    //if you multiply both of the equasions the result is the game
    //that's how deltaTime work
    std::chrono::duration<float> deltaTime;

    float r = 0.0f;
    while (!glfwWindowShouldClose(window)) {
        GLCall(glClear(GL_DEPTH_BUFFER_BIT));
        rend.ChangeBGColor(0.0f, 0.0f, 0.0f, 0.0f);
        //rend.Draw(vertexArray, indexBuffer, shaderProgram);

        //movement
        float cameraMoveSpeed = 5.0f * deltaTime.count();
        if (KeyHandleler::Get().IsKeyPressed(GLFW_KEY_W)) {
            cameraPos += cameraMoveSpeed * cameraFront;
        }
        if (KeyHandleler::Get().IsKeyPressed(GLFW_KEY_S)) {
            cameraPos -= cameraMoveSpeed * cameraFront;
        }
        if (KeyHandleler::Get().IsKeyPressed(GLFW_KEY_A)) {
            cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraMoveSpeed;
        }
        if (KeyHandleler::Get().IsKeyPressed(GLFW_KEY_D)) {
            cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraMoveSpeed;
        }
        glm::mat4 viewMat = glm::mat4(1.0f);
        viewMat = glm::lookAt(cameraPos, (cameraPos + cameraFront), cameraUp);
        shaderProgram.SetUniformMat4f("view", viewMat);

        //zooming
        glm::mat4 projMat = glm::mat4(1.0f);
        double scrollValue = 0.0f;
        MouseHandleler::Get().ReturnScrollInput((double*)0, &scrollValue);

        fov -= scrollValue;
        if (fov >= 45.0f)
            fov = 45.0f;
        else if (fov <= 1.0f)
            fov = 1.0f;

        projMat = glm::perspective(glm::radians(fov), (float)WIDTH / (float)HEIGHT, 1.0f, 100.0f);
        shaderProgram.SetUniformMat4f("projection", projMat);

        glDrawArrays(GL_TRIANGLES, 0, 36);

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