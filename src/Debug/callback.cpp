#include "callback.h"
#include "../Renderer/Renderer.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void error_callback(int error, const char *descr){
    std::filesystem::create_directories("../logs");
    std::ofstream fail("../logs/glfw_errors.txt", std::ios::app);
    if(fail.is_open()){
        fail << "[GLFW Error " << error << "]: " << descr << std::endl;
    }
}
void glfw_windowsize_callback(GLFWwindow* window, int width, int height){
    auto* renderer = static_cast<RenderW::RendererProg*>(glfwGetWindowUserPointer(window));
    if(renderer){
        renderer->resize(width, height);
        renderer->render();
        glfwSwapBuffers(window);
    }
}

void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    /*
    if(key == GLFW_KEY_ && GLFW_PRESS){

    }
    */
}
