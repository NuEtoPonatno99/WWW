#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Renderer{
    private:
        GLuint shaders_program = 0;
        GLuint vao = 0;
        GLuint points_vbo = 0;
        GLuint colors_vbo = 0;
        void initShaders();
        void initGeometry();
    public:
        Renderer();
        ~Renderer();

        void resize(int width, int height);
        void render();
};