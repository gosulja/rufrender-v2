#ifndef GUI_HPP
#define GUI_HPP

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>

#include "GuiThemes.hpp"
#include "Camera.hpp"
#include "ObjectManager.hpp"

class Gui {
public:
    Gui(GLFWwindow* window, ObjectManager* objectManager) : m_window(window), m_objectManager(objectManager) {
        Setup();
    }

    ~Gui() {
        Cleanup();
    }

    void BeginFrame() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void Draw(Camera& camera) {
        ImGui::Begin("Debug");

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

        if (ImGui::CollapsingHeader("Camera")) {
            ImGui::SliderFloat("Yaw", &camera.yaw, -180.0f, 180.0f);
            ImGui::SliderFloat("Pitch", &camera.pitch, -89.0f, 89.0f);
            ImGui::SliderFloat("Speed", &camera.speed, 0.0f, 10.0f);
            ImGui::SliderFloat("Sensitivity", &camera.sensitivity, 0.01f, 1.0f);
            ImGui::SliderFloat("Zoom", &camera.zoom, 1.0f, 120.0f);
        }

        if (ImGui::CollapsingHeader("Lighting")) {
            // Lighting controls here
        }

        if (ImGui::CollapsingHeader("Objects")) {
            auto objectsInfo = m_objectManager->GetObjectsInfo();
            for (const auto& info : objectsInfo) {
                ImGui::Text("%s", info.c_str());
            }
        }

        ImGui::End();
    }

    void EndFrame() {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

private:
    GLFWwindow* m_window;
    ObjectManager* m_objectManager;

    void Setup() {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;

        ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;

        GuiThemes::DeepDark();

        ImGui_ImplGlfw_InitForOpenGL(m_window, true);
        ImGui_ImplOpenGL3_Init("#version 330");
    }

    void Cleanup() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
};

#endif // GUI_HPP
