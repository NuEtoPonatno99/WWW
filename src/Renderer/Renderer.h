#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;

class Renderer{
    public:
        //для тр
        GLuint shader_program = 0;
        GLuint vao = 0;
        //для тр
        void resize(int width, int height);
        void render();
};
class Triangle{
    public:
        GLfloat points[9] = {
            0.0f, 0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f
        };
        GLfloat colors[9] = {
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f
        };
};
class Shaders{
    public:
        const char* vertex_shader =
        "#version 460\n"
        "layout(location = 0) in vec3 vertex_position;"
        "layout(location = 1) in vec3 vertex_color;"
        "out vec3 color;"
        "void main(){"
        "   color = vertex_color;"
        "   gl_Position = vec4(vertex_position, 1.0);"
        "}";
        const char* fragment_shader =
        "#version 460\n"
        "in vec3 color;"
        "out vec4 frag_color;"
        "void main(){"
        "   frag_color = vec4(color, 1.0);"
        "}";
};