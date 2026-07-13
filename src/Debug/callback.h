#pragma once
#include <iostream>
#include <fstream>
#include <filesystem>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void error_callback(int error, const char *descr);
void glfw_windowsize_callback(GLFWwindow* window, int width, int height);
void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);