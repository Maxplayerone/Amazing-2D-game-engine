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
#include"ECS/SpriteSheet.h"

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

    Renderer* rend = new Renderer();
    Shader shaderProgram("Assets/Shaders/Shader.shader");    

    //camera and stuff
    glm::mat4 modelMat = glm::mat4(1.0f); //identity matrix
    modelMat = glm::rotate(modelMat, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    modelMat = glm::scale(modelMat, glm::vec3(0.8f, 0.8f, 0.8f));

    glm::mat4 viewMat = glm::mat4(1.0f);

    glm::mat4 projMat = glm::mat4(1.0f);
    projMat = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, -1.0f, 1.0f);

   shaderProgram.SetUniformMat4f("model", modelMat);
   shaderProgram.SetUniformMat4f("view", viewMat); 
   shaderProgram.SetUniformMat4f("projection", projMat);
    
    //textures (to be abstracted)

    Texture trollTexture("Assets/Images/trollface.png", 1);
    Texture amogusTexture("Assets/Images/amogus.jpg", 2);
    Texture spriteSheetTex("Assets/Images/spritesheet.png", 3);
    std::cout << "Dimensions of spriteSheetTex (the whole spriteSheet)" << std::endl;
    std::cout << "Width " << spriteSheetTex.GetWidth() << " height " << spriteSheetTex.GetHeight() << std::endl << std::endl;

    //SpriteSheet* spriteSheet = new SpriteSheet(&spriteSheetTex, 16, 16, 26, 0);
    SpriteSheet* spriteSheet = new SpriteSheet(&spriteSheetTex, 16, 16, 26, 0);

    Sprite* testSprite = spriteSheet->GetSprite(9);

    shaderProgram.SetUniform1iv("u_Textures");

    GameObject* trollface = new GameObject("trollface");
    trollface->AddComponent(new SpriteRenderer(new Sprite(&spriteSheetTex, testSprite->GetTexCoords())));
    trollface->AddComponent(new Transform(-1.0f, -1.0f));
    
    /*
    GameObject* amogus = new GameObject("Amogus");
    amogus->AddComponent(new SpriteRenderer(1));
    amogus->AddComponent(new Transform(1.0f, -1.0f));
    */

    std::chrono::duration<float> deltaTime;

    float r = 0.0f;

    float modelScale = 1.0f;
    float modelIncVal = 0.1f;
    
    while (!glfwWindowShouldClose(window)) {     

    rend->ChangeBGColor(r, 0.74f, 0.91f, 0.0f);
    
    rend->DrawSingle(trollface, shaderProgram);
    //rend->DrawSingle(amogus, shaderProgram);
    //rend->DrawSingle(coloredCube, shaderProgram);
    //rend->DrawSingle(spriteSheetObj, shaderProgram);
    

    if (MouseHandleler::Get().IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
        if(r < 1.0f)
            r += 0.05f;
    if (MouseHandleler::Get().IsMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT))
        if(r > 0.0f)
            r -= 0.05f;

        if (currentScene != nullptr)
            currentScene->OnUpdate(deltaTime.count(), r);
          
        //zoom
            if (KeyHandleler::Get().IsKeyHeld(GLFW_KEY_Q))
                modelScale += modelIncVal;
            if (KeyHandleler::Get().IsKeyHeld(GLFW_KEY_W))
                modelScale -= modelIncVal;

           projMat = glm::ortho(-modelScale, modelScale, -modelScale, modelScale, -1.0f, 1.0f);
           shaderProgram.SetUniformMat4f("projection", projMat);

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