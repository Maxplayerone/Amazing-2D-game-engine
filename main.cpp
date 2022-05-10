#include<iostream>
#include"GL/glew.h"
#include <GLFW/glfw3.h>

#include"InputCallbacks.h"
#include"KeysHandleler.h"
#include"MouseHandleler.h"

#define WIDTH 640
#define HEIGHT 480

GLFWwindow* Init(void);
void Shutdown(void);


int main(void)
{
    GLFWwindow* window = Init();

    float r = 0.0f;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(r, 0.2f, 0.8f, 1.0f);

        if (MouseHandleler::Get().IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
            if (r < 255.0f)
                r += 0.01f;
         if (MouseHandleler::Get().IsMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT))
                if (r > 0.0f)
                    r -= 0.01f;
         
        glfwSwapBuffers(window);
        glfwPollEvents();
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
