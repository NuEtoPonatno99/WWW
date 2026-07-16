#include "ResourceManager.h"
#include "../Renderer/Renderer.h"
#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>

std::string ResourceManager::GetFileString(const std::string& rPath){
    std::ifstream f;
    f.open(m_path + "/" + rPath.c_str(), std::ios_base::in | std::ios_base::binary);
    if(!f.is_open()){
        ErrorLogRMan("Failed to open file: " + rPath);
        return std::string{};
    }
    std::stringstream buffer;
    buffer << f.rdbuf();
    return buffer.str();
}
ResourceManager::ResourceManager(const std::string& executPath){
    std::size_t found = executPath.find_last_of("/\\");
    m_path = executPath.substr(0, found);
}
std::shared_ptr<RenderW::RendererProg> ResourceManager::loadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath){
    std::string vertexString = GetFileString(vertexPath);
    if(vertexPath.empty()){
        ErrorLogRMan(vertexPath + " shader is empty\n");
        return nullptr;
    }
    std::string fragmentString = GetFileString(fragmentPath);
    if(fragmentPath.empty()){
        ErrorLogRMan(fragmentPath + " shader is empty\n");
        return nullptr;
    }
    std::shared_ptr<RenderW::RendererProg>& newShader = m_rendProg.emplace(shaderName, std::make_shared<RenderW::RendererProg>(vertexString, fragmentString)).first->second;
    if(newShader->isCompiled()){
        return newShader;
    }
    else{
        ErrorLogRMan("Cant load RendererProg:\n" "Vertex: " + vertexPath + "\n" + "Fragment: " + fragmentPath);
        return nullptr;
    }
}
std::shared_ptr<RenderW::RendererProg> ResourceManager::getShaderProgram(const std::string& shaderName){
    RendererProgMap::const_iterator it = m_rendProg.find(shaderName);
    if(it != m_rendProg.end()){
        return it->second;
    }
    ErrorLogRMan("Cant find the RendererProgram: " + shaderName);
    return nullptr;
}
void ResourceManager::loadTexture(const std::string& textureName, const std::string& texturePath){
    int channels = 0;
    int width;
    int height;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* pixels = stbi_load(std::string(m_path + "/" + texturePath).c_str(), &width, &height, &channels, 0);
    if(!pixels){
        ErrorLogRMan("Texture " + textureName + " cant load");
        return;
    }
    stbi_image_free(pixels);
}
void ResourceManager::ErrorLogRMan(const std::string& textError){
    std::filesystem::create_directories("../logs");
    std::ofstream fail("../logs/res_manager_errors.txt", std::ios::app);
    if(fail.is_open()){
        fail << textError << std::endl;
    }
    fail.close();
}