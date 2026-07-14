#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
//кастом завис
#include "Debug/callback.h"
#include "Renderer/Renderer.h"

using namespace std;

int g_xSizeWindow = 640;
int g_ySizeWindow = 420;

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

    GLFWwindow* window = glfwCreateWindow(g_xSizeWindow, g_ySizeWindow, "WW", NULL, NULL);
    if (!window)//окно не открылось
    {
        cout << "glfwCreateWindow failed!" << endl;
        glfwTerminate();
        return -1;
    }
    glfwSetWindowSizeCallback(window, glfw_windowsize_callback); //регулирует размер
    glfwSetKeyCallback(window, glfw_key_callback);//инпуты

    glfwMakeContextCurrent(window);

    if(!gladLoadGL()){
        cout << "Cant load GLAD" << endl;
        return -1;
    }

    glClearColor(0.75, .75, 0.75, 1);

    //иниц переменных
    double time = glfwGetTime();
    Renderer renderer;

    Triangle triangle;
    Shaders shaders;
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &(shaders.vertex_shader), nullptr);
    glCompileShader(vs);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &(shaders.fragment_shader), nullptr);
    glCompileShader(fs);
    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, vs);
    glAttachShader(shader_program, fs);
    glLinkProgram(shader_program);
    glDeleteShader(vs);
    glDeleteShader(fs);

    GLuint points_vbo = 0;
    glGenBuffers(1, &points_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle.points), triangle.points, GL_STATIC_DRAW);
    GLuint colors_vbo = 0;
    glGenBuffers(1, &colors_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle.colors), triangle.colors, GL_STATIC_DRAW);

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    renderer.shader_program = shader_program;
    renderer.vao = vao;
    glfwSetWindowUserPointer(window, &renderer);

    glfwSwapInterval(-1);//адаптивн буферизация

    if (glfwGetError(NULL) != GLFW_NO_ERROR) 
    {
        glfwSwapInterval(1);//обычная буферизация
    }
    //основной цикл рендеринга
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        renderer.render();

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}