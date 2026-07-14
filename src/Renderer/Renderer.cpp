#include "Renderer.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;

void Renderer::resize(int width, int height){
    glViewport(0, 0, width, height);

}
void Renderer::render(){
    glClear(GL_COLOR_BUFFER_BIT);
    if(shader_program != 0 && vao != 0){
        glUseProgram(shader_program);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
}