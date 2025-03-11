// This stops GLFW from including system's OpenGL headers (<GL/gl.h>), which would conflict with glbinding.
#define GLFW_INCLUDE_NONE
#define STB_IMAGE_IMPLEMENTATION // Define before including stb_image.h

#include <iostream>
#include <config.hpp>

#include <glbinding/gl/gl.h>
#include <glbinding/glbinding.h>
#include <glbinding/Version.h>
#include <glbinding-aux/Meta.h>
#include <glbinding-aux/ContextInfo.h>
#include <glbinding-aux/types_to_string.h>
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

    /* ~~Setting~~ */
    glfwSetErrorCallback([](int error, const char* description) -> void {
        std::cerr<<"GLFW Error: "<<description<<std::endl;
        return;
    });

    if(!glfwInit()){
        std::cerr<<"Failed to initialize GLFW"<<std::endl;
        std::cerr<<"Error Code: "<<glfwGetError(nullptr)<<std::endl;
        return -1;
    }

    /* ~~Create window~~ */
    // Set OpenGL version and profile mode
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    const unsigned int WIDTH = 640;
    const unsigned int HEIGHT = 480;

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Voronoi Diagram", NULL, NULL);
    if(!window){
        std::cerr<<"Failed to create window"<<std::endl;
        glfwTerminate();
        return -1;
    }

    // Set window icon
    int iconWidth, iconHeight, channels;
    unsigned char* imageData = stbi_load("assets/voronoi_icon.png", &iconWidth, &iconHeight, &channels, 4);
    if(!imageData){
        std::cerr<<"Failed to load icon image"<<std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }
    const GLFWimage icon = { iconWidth, iconHeight, imageData };

    glfwSetWindowIcon(window, 1, &icon);
    stbi_image_free(imageData);

    glfwMakeContextCurrent(window); // Make this window the current OpenGL context
    glfwSwapInterval(1); // Enable VSync

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
    std::cout<<"OpenGL Vendor: "<<glbinding::aux::ContextInfo::vendor()<<std::endl;
    std::cout<<"OpenGL Renderer: "<<glbinding::aux::ContextInfo::renderer()<<std::endl;

    /* ~~Initialize ImGui~~ */
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    [[maybe_unused]] ImGuiIO& io = ImGui::GetIO();

    // Bind ImGui to GLFW and set OpenGL shader version
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 460");

    ImGui::StyleColorsDark();

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

    // Terminate Libraries
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}