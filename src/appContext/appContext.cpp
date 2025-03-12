#include <iostream>
#include <string>

#include <glbinding/gl/gl.h>
#include <glbinding/glbinding.h>
#include <glbinding/Version.h>
#include <glbinding-aux/Meta.h>
#include <glbinding-aux/ContextInfo.h>
#include <glbinding-aux/types_to_string.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <appContext.hpp>

namespace App{
    bool init(Context& appContext, const unsigned int width, const unsigned int height, const std::string title){
        /* ~~Initialize GLFW~~ */
        glfwSetErrorCallback([](int error, const char* description) -> void {
            std::cerr<<"GLFW Error: "<<description<<std::endl;
            return;
        });

        if(!glfwInit()) return false;

        /* ~~Create window~~ */
        // Set OpenGL version and profile mode
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        auto& [window, windowWidth, windowHeight] = appContext;
        if(window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr); !window){
            std::cerr<<"Failed to create window"<<std::endl;
            glfwTerminate();
            return false;
        }
        windowWidth = width;
        windowHeight = height;

        // Set window icon
        int iconWidth, iconHeight, channels;
        unsigned char* imageData = stbi_load("assets/voronoi_icon.png", &iconWidth, &iconHeight, &channels, 4);
        if(!imageData){
            std::cerr<<"Failed to load icon image"<<std::endl;
            glfwDestroyWindow(window);
            glfwTerminate();
            return false;
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

        return true;
    }

    void terminate(Context& appContext){
        // Terminate ImGui
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        // Terminate GLFW
        glfwDestroyWindow(appContext.window);
        glfwTerminate();

        return;
    }
};