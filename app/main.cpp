// This stops GLFW from including system's OpenGL headers (<GL/gl.h>), which would conflict with glbinding.
#define GLFW_INCLUDE_NONE
#define STB_IMAGE_IMPLEMENTATION // Define before including stb_image.h

#include <iostream>
#include <string>
#include <config.hpp>

#include <glbinding/gl/gl.h>
#include <glbinding/glbinding.h>
#include <GLFW/glfw3.h> // GLFW include must be after glbinding
#include <stb_image.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <appContext.hpp>
#include <sidebar.hpp>
#include <graphics.hpp>

int test = OGL::xd;

int main(void){
    std::cout<<project_name<<std::endl;
    std::cout<<project_version<<std::endl;
    std::cout<<"GLFW version: "<<glfwGetVersionString()<<std::endl;
    std::cout<<"ImGui version: "<<ImGui::GetVersion()<<std::endl;

    /* ~~Inicialization~~ */
    App::Context appContext;
    const unsigned int initialWidth = 640;
    const unsigned int initialHeight = 480;
    const std::string title = "Voronoi Diagram";

    if(not App::init(appContext, initialWidth, initialHeight, title)){
        std::cerr<<"Failed to initialize application"<<std::endl;
        return -1;
    }
    auto& [
        window, initialWindowWidth, initialWindowHeight,
        arrowCursor, handCursor
    ] = appContext;

    const std::string sidebarTitle = "Control Panel";
    GUI::Sidebar sidebar(sidebarTitle, &appContext);

    int currentWindowWidth, currentWindowHeight;

    /* ~~Main loop~~ */
    do{
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        glfwGetFramebufferSize(window, &currentWindowWidth, &currentWindowHeight);
        sidebar.render(currentWindowWidth, currentWindowHeight);

        ImGui::Render();
        gl::glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        gl::glClear(gl::GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }while(!glfwWindowShouldClose(window));

    App::terminate(appContext);

    return 0;
}