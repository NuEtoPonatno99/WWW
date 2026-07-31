#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <map>

namespace RenderW{
    class RendererProg;
    class Texture2D;
    class Sprite;
}

class ResourceManager{
    private:
        typedef std::map<const std::string, std::shared_ptr<RenderW::RendererProg>> RendererProgMap;
        RendererProgMap m_rendProg;
        typedef std::map<const std::string, std::shared_ptr<RenderW::Texture2D>> TexturesMap;
        TexturesMap m_texturesMap;
        typedef std::map<const std::string, std::shared_ptr<RenderW::Sprite>> SpritesMap;
        SpritesMap m_spritesMap;
        std::string m_path;
        std::string GetFileString(const std::string& rPath);
        void ErrorLogRMan(const std::string& textError);
    public:
        ResourceManager(const std::string& executPath);
        ~ResourceManager() = default;

        ResourceManager(const ResourceManager&) = delete;
        ResourceManager& operator = (const ResourceManager&) = delete;
        ResourceManager& operator = (ResourceManager&&) = delete;
        ResourceManager(ResourceManager&&) = delete;

        std::shared_ptr<RenderW::RendererProg> loadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath);
        std::shared_ptr<RenderW::RendererProg> getShaderProgram(const std::string& shaderName);

        std::shared_ptr<RenderW::Texture2D> loadTexture(const std::string& textureName, const std::string& texturePath);
        std::shared_ptr<RenderW::Texture2D> getTexture(const std::string& textureName);

        std::shared_ptr<RenderW::Sprite> loadSprite(const std::string& spriteName,
                                                   const std::string& textureName,
                                                   const std::string& shaderName,
                                                   const unsigned int spriteWidth,
                                                   const unsigned int spriteHeight);
        std::shared_ptr<RenderW::Sprite> getSprite(const std::string& spriteName);
};