#pragma once
#include <glad/glad.h>
#include <string>

namespace RenderW{
    class Texture2D{
        private:
            GLuint m_texturesID;
            GLenum m_mode;
            unsigned m_width;
            unsigned m_height;
        public:
            Texture2D(const GLuint width, const GLuint height,
                const unsigned char* data, const unsigned int channels,
                const GLenum& filter, const GLenum& wrapMode);
/*про filter: GL_NEAREST - оч четкое;GL_LINEAR - этот парень шакал
про wrapMode: GL_REPEAT - повторение текстуры;
GL_MIRRORED_REPEAT - отзеркаливание текстуры;GL_CLAMP_TO_EDGE - повторение последнего пикселя;
GL_CLAMP_TO_BORDER - закрашивание спец цветом*/
            ~Texture2D();

            Texture2D() = delete;
            Texture2D(const Texture2D&) = delete;
            Texture2D& operator = (const Texture2D&) = delete;
            Texture2D& operator = (Texture2D&& texture2D);
            Texture2D(Texture2D&& texture2D);

            void bind() const;
    };
}