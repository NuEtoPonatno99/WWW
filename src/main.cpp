#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
//кастом завис
#include "Debug/callback.h"
#include "Renderer/Renderer.h"
#include "ManagerRes/ResourceManager.h"
#include "Renderer/Texture2D.h"
#include "Renderer/Sprite.h"

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
        auto DefaultSpriteProgram = resourceManager.loadShaders("SpriteShader", "res/shaders/Vsprite_shader.txt", "res/shaders/Fsprite_shader.txt");
        if(!DefaultShaderProgram || !DefaultSpriteProgram){
            return -1;
        }
        auto tex = resourceManager.loadTexture("DefTexture", "res/textures/www.png");
        auto spr = resourceManager.loadSprite("DefSprite", "DefTexture", "SpriteShader", 50, 100);
        spr->setPosition(glm::vec2(300, 100));

        DefaultShaderProgram->render();
        DefaultShaderProgram->setInt("tex", 0);//второй аргумент - номер слота текстуры

        DefaultSpriteProgram->render();
        DefaultSpriteProgram->setInt("tex", 0);//второй аргумент - номер слота текстуры

        glm::mat4 modelMatrix = glm::mat4(1.f);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(100.f, 0.f, 0.f));

        glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(g_windSize.x), 0.f, static_cast<float>(g_windSize.y), -100.f, 100.f);

        glfwSetWindowUserPointer(window, DefaultShaderProgram.get());

        DefaultShaderProgram->setMatrix4("projectionMat", projectionMatrix);

        DefaultSpriteProgram->setMatrix4("projectionMat", projectionMatrix);

        glfwSwapInterval(-1);//адаптивн буферизация
        if (glfwGetError(NULL) != GLFW_NO_ERROR) 
        {
            glfwSwapInterval(1);//обычная буферизация
        }
        //основной цикл рендеринга
        while (!glfwWindowShouldClose(window))
        {
            tex->bind();
            DefaultShaderProgram->setMatrix4("modelMat", modelMatrix);
            DefaultShaderProgram->render();

            spr->render();

            glfwSwapBuffers(window);

            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}