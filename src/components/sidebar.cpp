#include <string>
#include <imgui.h>

#include <sidebar.hpp>

namespace GUI{
    void Sidebar::render(const int windowWidth, const int windowHeight){
        /* ~~Sidebar settings~~ */
        ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(
            static_cast<float>(windowWidth) * 0.25f,
            static_cast<float>(windowHeight)
        ));

        ImGui::Begin(this->sidebarTitle.c_str(), nullptr, this->sidebarFlags);

        /* ~~Draw elements~~ */
        // this->drawPerformanceMetrics();
        ImGui::Separator();
        // this->drawControls();

        ImGui::End();
    }
};