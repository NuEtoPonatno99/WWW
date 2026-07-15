#include "Renderer.h"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Renderer::Renderer(){
    initShaders();
    initGeometry();
}
Renderer::~Renderer(){
    glDeleteBuffers(1, &points_vbo);
    glDeleteBuffers(1, &colors_vbo);
    glDeleteVertexArrays(1, &vao);
    glDeleteProgram(shaders_program);
}
void Renderer::initShaders(){
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

        GLuint vs = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vs, 1, &vertex_shader, nullptr);
        glCompileShader(vs);
        GLint success;
        glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
        if(!success){
            GLchar infoLog[512];
            glGetShaderInfoLog(vs, 512, nullptr, infoLog);
            std::filesystem::create_directories("../logs");
            std::ofstream fail("../logs/shaders_errors.txt", std::ios::app);
            if(fail.is_open()){
                fail << "ERROR::VERTEX_SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
            }
        }

        GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fs, 1, &fragment_shader, nullptr);
        glCompileShader(fs);
        glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
        if(!success){
            GLchar infoLog[512];
            glGetShaderInfoLog(fs, 512, nullptr, infoLog);
            std::filesystem::create_directories("../logs");
            std::ofstream fail("../logs/shaders_errors.txt", std::ios::app);
            if(fail.is_open()){
                fail << "ERROR::FRAGMENT_SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
            }
        }

        shaders_program = glCreateProgram();
        glAttachShader(shaders_program, vs);
        glAttachShader(shaders_program, fs);
        glLinkProgram(shaders_program);
        glDeleteShader(vs);
        glDeleteShader(fs);

}
void Renderer::initGeometry(){
        //тр
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
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glGenBuffers(1, &points_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
        glGenBuffers(1, &colors_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        //тр
}
void Renderer::resize(int width, int height){
    glViewport(0, 0, width, height);
}
void Renderer::render(){
    glClear(GL_COLOR_BUFFER_BIT);
    if(shaders_program != 0 && vao != 0){
        glUseProgram(shaders_program);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
}