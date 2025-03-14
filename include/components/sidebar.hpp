#pragma once

#include <string>
#include <imgui.h>
#include <glfw/glfw3.h>

#include <appContext.hpp>

namespace GUI{
    class Sidebar{
        private:
            std::string sidebarTitle;
            float sidebarWidth;
            unsigned int voronoiPoints;
            bool runningState;

            App::Context* appContext;
            GLFWcursor* currentCursor;
            GLFWcursor* lastCursor;

            const ImGuiWindowFlags sidebarFlags =
                ImGuiWindowFlags_NoResize |
                ImGuiWindowFlags_NoMove   |
                ImGuiWindowFlags_NoSavedSettings;

            void drawPerformanceMetrics() const;
            void drawControls();
        public:
            Sidebar() = default;
            Sidebar(const std::string title, App::Context* context):
                sidebarTitle(title),
                sidebarWidth(0.25f),
                voronoiPoints(0U),
                runningState(false),
                appContext(context),
                currentCursor(nullptr),
                lastCursor(nullptr)
            {};
            ~Sidebar() = default;

            void render(const int windowWidth, const int windowHeight);

            bool isRunning() const;
            void setRunning(const bool state);

            unsigned int getVoronoiPoints() const;
            void increaseVoronoiPoints();
    };
};