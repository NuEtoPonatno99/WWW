#pragma once
#include <glad/glad.h>
#include <glm/vec2.hpp>
#include <memory>

namespace RenderW{
    class Texture2D;
    class RendererProg;
    class Sprite{
        private:
            std::shared_ptr<Texture2D> m_Texture;
            std::shared_ptr<RendererProg> m_RendererProg;
            glm::vec2 m_pos;
            glm::vec2 m_size;
            float m_rotation;
            GLuint m_vao;
            GLuint m_vertexCoordsVbo;
            GLuint m_textureVbo;
        public:
            Sprite(const std::shared_ptr<Texture2D> pTexture, const std::shared_ptr<RendererProg> pRendererProg,
            const glm::vec2& pos=glm::vec2(0.f), 
            const glm::vec2 size=glm::vec2(1.f),
            const float rotation=0.f);
            ~Sprite();

            void setPosition(const glm::vec2& pos);
            void setSize(const glm::vec2& size);
            void setRotation(const float rotation);

            Sprite(const Sprite&) = delete;
            Sprite& operator = (const Sprite&) = delete;

            void render() const;
    };
}