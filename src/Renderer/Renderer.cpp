#include "Renderer.h"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace RenderW{
    RendererProg::RendererProg(){
        initShaders();
        initGeometry();
    }
    RendererProg::~RendererProg(){
        glDeleteBuffers(1, &points_vbo);
        glDeleteBuffers(1, &colors_vbo);
        glDeleteVertexArrays(1, &vao);
        glDeleteProgram(shaders_program);
    }
    bool RendererProg::createShader(const std::string& source, const GLenum shaderType, GLuint& shaderID){
        shaderID = glCreateShader(shaderType);
        const char* code = source.c_str();
        glShaderSource(shaderID, 1, &code, nullptr);
        glCompileShader(shaderID);
        GLint success;
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
        if(!success){
            GLchar infoLog[512];
            glGetShaderInfoLog(shaderID, 512, nullptr, infoLog);
            std::filesystem::create_directories("../logs");
            std::ofstream fail("../logs/shaders_errors.txt", std::ios::app);
            if(fail.is_open()){
                fail << "ERROR:: " << shaderType << "::COMPILATION_FAILED\n" << infoLog << std::endl;
            }
            return false;
        }
        return true;
    }
    void RendererProg::initShaders(){
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

            GLuint vShID;
            if(!createShader(vertex_shader, GL_VERTEX_SHADER, vShID)){
                return;
            }
            GLuint fShID;
            if(!createShader(fragment_shader, GL_FRAGMENT_SHADER, fShID)){
                glDeleteShader(vShID);
                return;
            }

            shaders_program = glCreateProgram();
            glAttachShader(shaders_program, vShID);
            glAttachShader(shaders_program, fShID);
            glLinkProgram(shaders_program);

            GLint success;
            glGetProgramiv(shaders_program, GL_LINK_STATUS, &success);
            if(!success){
                GLchar infoLog[512];
                glGetProgramInfoLog(shaders_program, 512, nullptr, infoLog);
                std::filesystem::create_directories("../logs");
                std::ofstream fail("../logs/shaders_errors.txt", std::ios::app);
                if(fail.is_open()){
                    fail << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
                }
            }
            else{
                isCompiled = true;
            }
            glDeleteShader(vShID);
            glDeleteShader(fShID);

    }
    void RendererProg::initGeometry(){
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
    void RendererProg::resize(int width, int height){
        glViewport(0, 0, width, height);
    }
    void RendererProg::render(){
        glClear(GL_COLOR_BUFFER_BIT);
        if(shaders_program != 0 && vao != 0){
            glUseProgram(shaders_program);
            glBindVertexArray(vao);
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }
    }
}
