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

int main(void){
    std::cout<<project_name<<std::endl;
    std::cout<<project_version<<std::endl;
    std::cout<<"GLFW version: "<<glfwGetVersionString()<<std::endl;
    std::cout<<"ImGui version: "<<ImGui::GetVersion()<<std::endl;

    /* ~~Inicialization~~ */
    App::Context appContext;
    const unsigned int width = 640;
    const unsigned int height = 480;

    if(not App::init(appContext, width, height, "Voronoi Diagram")){
        const char** GLFWerror;
        std::cerr<<"Failed to initialize application"<<std::endl;
        std::cerr<<"GLFW Error Code: "<<glfwGetError(GLFWerror)<<std::endl;
        return -1;
    }
    auto& [window, windowWidth, windowHeight] = appContext;

    /* ~~Main loop~~ */
    do{
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Hola ImGUI");
        ImGui::Text("Hola Crayola");
        ImGui::End();

        gl::glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        gl::glClear(gl::GL_COLOR_BUFFER_BIT);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }while(!glfwWindowShouldClose(window));

    App::terminate(appContext);

    return 0;
}