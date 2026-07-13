#include "logger.h"
#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;

void error_callback(int error, const char *descr){
    filesystem::create_directories("../logs");
    ofstream fail("../logs/glfw_errors.txt", ios::app);
    if(fail.is_open()){
        fail << "[GLFW Error " << error << "]: " << descr << endl;
    }
    cerr << "[GLFW Error " << error << "]: " << descr << endl; 
}