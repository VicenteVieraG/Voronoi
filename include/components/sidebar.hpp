#pragma once
#include <string>
#include <imgui.h>

namespace GUI{
    class Sidebar{
        private:
            std::string sidebarTitle;
            float sidebarWidth;
            unsigned int voronoiPoints;
            bool runningState;

            const ImGuiWindowFlags sidebarFlags =
                ImGuiWindowFlags_NoResize |
                ImGuiWindowFlags_NoMove   |
                ImGuiWindowFlags_NoSavedSettings;

            void drawControls();
            void drawPerformanceMetrics() const;
        public:
            Sidebar() = default;
            Sidebar(const std::string title):
                sidebarTitle(title),
                voronoiPoints(0U),
                runningState(false)
            {};

            void render(const int windowWidth, const int windowHeight);

            bool isRunning() const;
            void setRunning(const bool state);

            unsigned int getVoronoiPoints() const;
            void setVoronoiPoints();
    };
};