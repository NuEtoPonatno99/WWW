#include "callback.h"
#include "../Renderer/Renderer.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;


void error_callback(int error, const char *descr){
    filesystem::create_directories("../logs");
    ofstream fail("../logs/glfw_errors.txt", ios::app);
    if(fail.is_open()){
        fail << "[GLFW Error " << error << "]: " << descr << endl;
    }
    cerr << "[GLFW Error " << error << "]: " << descr << endl; 
}
void glfw_windowsize_callback(GLFWwindow* window, int width, int height){
    Renderer* renderer = static_cast<Renderer*>(glfwGetWindowUserPointer(window));
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
