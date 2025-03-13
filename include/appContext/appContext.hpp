#pragma once

#include <string>
#include <glfw/glfw3.h>

namespace App{
    struct Context{
        GLFWwindow* window;
        unsigned int windowWidth;
        unsigned int windowHeight;

        GLFWcursor* arrowCursor;
        GLFWcursor* handCursor;
    };

    bool init(Context& appContext, const unsigned int width, const unsigned int height, const std::string title);
    void terminate(Context& appContext);
};