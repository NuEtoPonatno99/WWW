#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
//кастом завис
#include "Debug/logger.h"

using namespace std;


int main(void)
{
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()){
        cout << "glfwInit failed!" << endl;
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(640, 480, "WW", NULL, NULL);
    if (!window)//окно не открылось
    {
        cout << "glfwCreateWindow failed!" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if(!gladLoadGL()){
        cout << "Cant load GLAD" << endl;
        return -1;
    }
    //иниц переменных
    double time = glfwGetTime();


    glClearColor(0.75, .75, 0.75, 1);
    glfwSwapInterval(-1);//адаптивн буферизация

    if (glfwGetError(NULL) != GLFW_NO_ERROR) 
    {
        glfwSwapInterval(1);//обычная буферизация
    }
    //основной цикл рендеринга
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}