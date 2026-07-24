#include "Sprite.h";
#include "Renderer.h";
#include "Texture2D.h";
#include <glm/mat4x4.hpp>;
#include <glm/gtc/matrix_transform.hpp>;

namespace RenderW{
        Sprite::Sprite(const std::shared_ptr<Texture2D> pTexture, const std::shared_ptr<RendererProg> pRendererProg,
        const glm::vec2& pos=glm::vec2(0.f), 
        const glm::vec2 size=glm::vec2(1.f),
        const float rotation=0.f)
        : m_RendererProg(std::move(pRendererProg)), m_Texture(std::move(pTexture)), m_pos(pos), m_size(size), m_rotation(rotation){
            GLfloat vertexCoords[] = {
                0.0f, 0.0f,
                0.0f, 1.0f,
                1.0f, 1.0f,
                1.0f, 1.0f,
                1.0f, 0.0f,
                0.0f, 0.0f
            };
            GLfloat textureCoords[] = {
                0.0f, 0.0f,
                0.0f, 1.0f,
                1.0f, 1.0f,
                1.0f, 1.0f,
                1.0f, 0.0f,
                0.0f, 0.0f
            };
            glGenVertexArrays(1, &m_vao);
            glBindVertexArray(m_vao);


            glGenBuffers(1, &m_vertexCoordsVbo);
            glBindBuffer(GL_ARRAY_BUFFER, m_vertexCoordsVbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertexCoords), &vertexCoords, GL_STATIC_DRAW);

            glGenBuffers(1, &m_textureVbo);
            glBindBuffer(GL_ARRAY_BUFFER, m_textureVbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(textureCoords), textureCoords, GL_STATIC_DRAW);

            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, m_vertexCoordsVbo);
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

            glEnableVertexAttribArray(1);
            glBindBuffer(GL_ARRAY_BUFFER, m_textureVbo);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }
        Sprite::~Sprite(){
            glDeleteBuffers(1, &m_vertexCoordsVbo);
            glDeleteBuffers(1, &m_textureVbo);
            glDeleteVertexArrays(1, &m_vao);
        }

        void Sprite::setPosition(const glm::vec2& pos){
            m_pos = pos;
        }
        void Sprite::setSize(const glm::vec2& size){
            m_size=size;
        }
        void Sprite::setRotation(const float rotation){
            m_rotation = rotation;
        }

        void Sprite::render() const{
            m_RendererProg->render();
            glm::mat4 model(1.0f);
            model = glm::scale(model, glm::vec3(m_size, 1.0f));// скалировние матрицы
        }
}