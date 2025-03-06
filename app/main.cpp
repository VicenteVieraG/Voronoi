// This stops GLFW from including system's OpenGL headers (<GL/gl.h>)
// which would conflict with glbinding
#define GLFW_INCLUDE_NONE

#include <iostream>
#include <config.hpp>

#include <glbinding/gl/gl.h>
#include <glbinding/glbinding.h>
#include <glbinding/Version.h>
#include <glbinding-aux/Meta.h>
#include <glbinding-aux/ContextInfo.h>
#include <glbinding-aux/types_to_string.h>
#include <GLFW/glfw3.h> // GLFW include must be after glbinding

int main(void){
    std::cout<<project_name<<std::endl;
    std::cout<<project_version<<std::endl;
    std::cout<<"GLFW version: "<<glfwGetVersionString()<<std::endl;

    /* ~~Setting~~ */
    glfwSetErrorCallback([](int error, const char* description) -> void {
        std::cerr<<"GLFW Error: "<<description<<std::endl;
        return;
    });

    if(!glfwInit()){
        std::cerr<<"Failed to initialize GLFW"<<std::endl;
        return -1;
    }

    /* ~~Create window~~ */
    // Set OpenGL version and profile mode
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    const unsigned int WIDTH = 640;
    const unsigned int HEIGHT = 480;

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Hola Crayola", NULL, NULL);
    if(!window){
        std::cerr<<"Failed to create window"<<std::endl;
        glfwTerminate();
        return -1;
    }

    // Make this window the current OpenGL context
    glfwMakeContextCurrent(window);

    // Window's resize callback
    glfwSetFramebufferSizeCallback(window,
        [](GLFWwindow* window, int width, int height) -> void {
            gl::glViewport(0, 0, width, height);
            return;
        }
    );

    /* ~~glbinding inicialization~~ */
    glbinding::initialize(glfwGetProcAddress);

    // Print OpenGL information
    std::cout<<"OpenGL Version: "<<glbinding::aux::ContextInfo::version()<<std::endl;
    std::cout<<"OpenGL Vendor: "<<glbinding::aux::ContextInfo::vendor() <<std::endl;
    std::cout<<"OpenGL Renderer: "<<glbinding::aux::ContextInfo::renderer()<<std::endl;

    /* ~~Main loop~~ */
    do{
        glfwPollEvents();
        gl::glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        gl::glClear(gl::GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
    }while(!glfwWindowShouldClose(window));

    // Terminate GLFW
    glfwTerminate();

    return 0;
}