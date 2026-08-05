#pragma once
#include <iostream>
#include <memory>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>

namespace RenderW{
    class RendererProg{
        private:
            GLuint m_shaders_program = 0;
            GLuint m_vao = 0;
            GLuint m_points_vbo = 0;
            GLuint m_colors_vbo = 0;
            GLuint m_texture_vbo = 0;
            bool m_isCompiled = false;
            void initShaders(std::string vertex_shader, std::string fragment_shader);
            bool createShader(const std::string& source, const GLenum shaderType, GLuint& shaderID);
            //figures
            void Triangle();
        public:
            RendererProg(const std::string& vertexShader, const std::string& fragmentShader);
            ~RendererProg();

            RendererProg() = delete;
            RendererProg(RendererProg&) = delete;
            RendererProg& operator = (const RendererProg&) = delete;
            RendererProg& operator = (RendererProg&& rendererProg) noexcept;
            RendererProg(RendererProg&& rendererProg) noexcept;

            void initGeometry();
            bool isCompiled() const {return m_isCompiled;}
            void setInt(const std::string name, const GLint value);
            void setMatrix4(const std::string& name, const glm::mat4& matrix);
            GLuint getProgID();
            void resize(int width, int height);
            void render();
    };
    struct WindowShaders{
        std::shared_ptr<RenderW::RendererProg> geometryShader;
        std::shared_ptr<RenderW::RendererProg> spriteShader;
    };
}