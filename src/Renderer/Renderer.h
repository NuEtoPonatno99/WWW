#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace RenderW{
    class RendererProg{
        private:
            GLuint shaders_program = 0;
            GLuint vao = 0;
            GLuint points_vbo = 0;
            GLuint colors_vbo = 0;
            bool isCompiled;
            void initShaders();
            void initGeometry();
            bool createShader(const std::string& source, const GLenum shaderType, GLuint& shaderID);
        public:
            RendererProg();
            ~RendererProg();

            void resize(int width, int height);
            void render();
    };
}