#include "callback.h"
#include "../Renderer/Renderer.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

void error_callback(int error, const char *descr){
    std::filesystem::create_directories("../logs");
    std::ofstream fail("../logs/glfw_errors.txt", std::ios::app);
    if(fail.is_open()){
        fail << "[GLFW Error " << error << "]: " << descr << std::endl;
    }
}
void glfw_windowsize_callback(GLFWwindow* window, int width, int height){
    /*
    auto* renderer = static_cast<RenderW::RendererProg*>(glfwGetWindowUserPointer(window));
    if(renderer){
        renderer->resize(width, height);
        renderer->render();
        glfwSwapBuffers(window);
    }
    */
    auto* shaders = static_cast<RenderW::WindowShaders*>(glfwGetWindowUserPointer(window));
    if(shaders){
        glViewport(0, 0, width, height);

        glm::mat4 newProjection = glm::ortho(0.f, static_cast<float>(width), 0.f, static_cast<float>(height), -100.f, 100.f);

        if(shaders->geometryShader) {   
            shaders->geometryShader->setMatrix4("projectionMat", newProjection);
        }
        if(shaders->spriteShader) {
            shaders->spriteShader->setMatrix4("projectionMat", newProjection);
        }
    }
}

void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    /*
    if(key == GLFW_KEY_ && GLFW_PRESS){

    }
    */
}
