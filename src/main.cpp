#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <glm/vec2.hpp>
//кастом завис
#include "Debug/callback.h"
#include "Renderer/Renderer.h"
#include "ManagerRes/ResourceManager.h"
#include "Renderer/Texture2D.h"

glm::ivec2 g_windSize(640, 480);

int main(int argc, char** argv)
{
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()){
        std::cout << "glfwInit failed!" << std::endl;
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(g_windSize.x, g_windSize.y, "WW", nullptr, nullptr);
    if (!window)//окно не открылось
    {
        std::cout << "glfwCreateWindow failed!" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwSetWindowSizeCallback(window, glfw_windowsize_callback); //регулирует размер
    glfwSetKeyCallback(window, glfw_key_callback);//инпуты

    glfwMakeContextCurrent(window);

    if(!gladLoadGL()){
        std::cout << "Cant load GLAD" << std::endl;
        return -1;
    }

    glClearColor(0.75, .75, 0.75, 1);

    //иниц переменных
    double time = glfwGetTime();
    {
        ResourceManager resourceManager(argv[0]);
        auto DefaultShaderProgram = resourceManager.loadShaders("DefShader", "res/shaders/vertex_shader.txt", "res/shaders/fragment_shader.txt");
        if(!DefaultShaderProgram){
            return -1;
        }
        auto tex = resourceManager.loadTexture("DefTexture", "res/textures/www.png");
        DefaultShaderProgram->render();
        DefaultShaderProgram->setInt("tex", 0);//второй аргумент - номер слота текстуры

        glfwSetWindowUserPointer(window, &DefaultShaderProgram);

        glfwSwapInterval(-1);//адаптивн буферизация
        if (glfwGetError(NULL) != GLFW_NO_ERROR) 
        {
            glfwSwapInterval(1);//обычная буферизация
        }
        //основной цикл рендеринга
        while (!glfwWindowShouldClose(window))
        {
            tex->bind();
            DefaultShaderProgram->render();

            glfwSwapBuffers(window);

            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}