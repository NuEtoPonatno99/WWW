#include "Renderer.h"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace RenderW{
    RendererProg::RendererProg(const std::string& vertexShader, const std::string& fragmentShader){
        initShaders(vertexShader, fragmentShader);
        initGeometry();
    }
    RendererProg::~RendererProg(){
        glDeleteBuffers(1, &m_points_vbo);
        glDeleteBuffers(1, &m_colors_vbo);
        glDeleteVertexArrays(1, &m_vao);
        glDeleteProgram(m_shaders_program);
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
    void RendererProg::setInt(const std::string name, const GLint value){
        glUniform1i(glGetUniformLocation(m_shaders_program, name.c_str()), value);
    }
    void RendererProg::initShaders(std::string vertex_shader, std::string fragment_shader){
            GLuint vShID;
            if(!createShader(vertex_shader, GL_VERTEX_SHADER, vShID)){
                return;
            }
            GLuint fShID;
            if(!createShader(fragment_shader, GL_FRAGMENT_SHADER, fShID)){
                glDeleteShader(vShID);
                return;
            }

            m_shaders_program = glCreateProgram();
            glAttachShader(m_shaders_program, vShID);
            glAttachShader(m_shaders_program, fShID);
            glLinkProgram(m_shaders_program);

            GLint success;
            glGetProgramiv(m_shaders_program, GL_LINK_STATUS, &success);
            if(!success){
                GLchar infoLog[512];
                glGetProgramInfoLog(m_shaders_program, 512, nullptr, infoLog);
                std::filesystem::create_directories("../logs");
                std::ofstream fail("../logs/shaders_errors.txt", std::ios::app);
                if(fail.is_open()){
                    fail << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
                }
            }
            else{
                m_isCompiled = true;
            }
            glDeleteShader(vShID);
            glDeleteShader(fShID);
    }
    void RendererProg::initGeometry(){
            //тр
            GLfloat points[] = {
                0.0f, 0.5f, 0.0f,
                0.5f, -0.5f, 0.0f,
                -0.5f, -0.5f, 0.0f
            };
            GLfloat colors[] = {
                1.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 1.0f
            };
            GLfloat texture[] = {
                0.5f, 1.0f,
                1.0f, 0.0f,
                0.0f, 0.0f
            };
            glGenVertexArrays(1, &m_vao);
            glBindVertexArray(m_vao);

            glGenBuffers(1, &m_points_vbo);
            glBindBuffer(GL_ARRAY_BUFFER, m_points_vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
            glGenBuffers(1, &m_colors_vbo);
            glBindBuffer(GL_ARRAY_BUFFER, m_colors_vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
            glGenBuffers(1, &m_texture_vbo);
            glBindBuffer(GL_ARRAY_BUFFER, m_texture_vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(texture), texture, GL_STATIC_DRAW);

            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, m_points_vbo);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
            glEnableVertexAttribArray(1);
            glBindBuffer(GL_ARRAY_BUFFER, m_colors_vbo);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
            glEnableVertexAttribArray(2);
            glBindBuffer(GL_ARRAY_BUFFER, m_texture_vbo);
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
            glBindVertexArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            //тр
    }
    void RendererProg::resize(int width, int height){
        glViewport(0, 0, width, height);
    }
    void RendererProg::render(){
        glClear(GL_COLOR_BUFFER_BIT);
        if(m_shaders_program != 0 && m_vao != 0){
            glUseProgram(m_shaders_program);
            glBindVertexArray(m_vao);
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }
    }
    RendererProg& RendererProg::operator = (RendererProg&& rendererProg) noexcept{
        glDeleteProgram(m_shaders_program);
        m_shaders_program = rendererProg.m_shaders_program;
        m_isCompiled = rendererProg.m_isCompiled;
        rendererProg.m_shaders_program = 0;
        rendererProg.m_isCompiled = false;
        return *this;
    }
    RendererProg::RendererProg(RendererProg&& rendererProg) noexcept{
        m_shaders_program = rendererProg.m_shaders_program;
        m_isCompiled = rendererProg.m_isCompiled;
        rendererProg.m_shaders_program = 0;
        rendererProg.m_isCompiled = false;
    }
}