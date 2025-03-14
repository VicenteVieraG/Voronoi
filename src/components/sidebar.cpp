#include <iostream>
#include <string>
#include <imgui.h>

#include <appContext.hpp>
#include <sidebar.hpp>

namespace GUI{
    void Sidebar::render(const int windowWidth, const int windowHeight){
        /* ~~Sidebar settings~~ */
        ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(
            static_cast<float>(windowWidth) * this->sidebarWidth,
            static_cast<float>(windowHeight)
        ));

        ImGui::Begin(this->sidebarTitle.c_str(), nullptr, this->sidebarFlags);

        /* ~~Draw elements~~ */
        this->drawPerformanceMetrics();
        ImGui::Separator();
        this->drawControls();

        ImGui::End();
        return;
    }

    void Sidebar::drawPerformanceMetrics() const {
        ImGui::Text("Performance");
        ImGui::Spacing();

        const ImGuiIO& io = ImGui::GetIO();
        ImGui::Text("FPS: %.1f", io.Framerate);
        ImGui::Text("Frame Time: %.3f ms", 1000.0f / io.Framerate);
        return;
    }

    void Sidebar::drawControls(){
        ImGui::Text("Controls");
        ImGui::Separator();
        ImGui::Spacing();

        if(ImGui::Button(this->runningState ? "Stop" : "Start", ImVec2(-1.0f, 0.0f))){
            this->runningState = !this->runningState;
            std::cout<<"PRESSED\n";
        }

        ImGui::IsItemHovered() ?
            this->currentCursor = this->appContext->handCursor :
            this->currentCursor = this->appContext->arrowCursor;
        glfwSetCursor(this->appContext->window, this->currentCursor);

        return;
    }

    /* ~~Getters and Setters~~ */

    bool Sidebar::isRunning() const {
        return this->runningState;
    }
    void Sidebar::setRunning(const bool state){
        this->runningState = state;
        return;
    }

    unsigned int Sidebar::getVoronoiPoints() const {
        return this->voronoiPoints;
    }
    void Sidebar::increaseVoronoiPoints(){
        this->voronoiPoints++;
        return;
    }
};