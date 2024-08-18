#pragma once
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include <string>


class popup {
public:
    popup(const std::string& message) : message(message), isOpen(true) {}

    void render() {
        if (isOpen) {
            ImGui::OpenPopup("Popup");

            if (ImGui::BeginPopupModal("Popup", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
                ImGui::Text("%s", message.c_str());

                if (ImGui::Button("OK")) {
                    ImGui::CloseCurrentPopup();
                    isOpen = false;
                }

                ImGui::EndPopup();
            }
        }
    }

    void close() {
        isOpen = false;
    }

    bool is_open() const {
        return isOpen;
    }

private:
    std::string message;
    bool isOpen;
};

