#include "layers/script_debug_layer.h"
#include "other utils/common.h"

wizm::script_debug_layer::script_debug_layer()
{
}

wizm::script_debug_layer::~script_debug_layer()
{
}

void wizm::script_debug_layer::OnAttach()
{
}

void wizm::script_debug_layer::OnDetach()
{
}

void wizm::script_debug_layer::update(float delta_time)
{
	ImGui::Begin("Debug");
    ImVec4 bg_color = ImVec4(0.1f, 0.1f, 0.1f, 1.0f);
    ImVec4 warning_text_color = ImVec4(1, 1, 0, 1);
    ImVec4 error_text_color = ImVec4(1, 0, 0, 1);
    ImVec4 crnt_color = ImVec4(1, 1, 1, 1);

    ImGui::BeginChild("Console", ImVec2(0, 0), true, ImGuiWindowFlags_AlwaysVerticalScrollbar);

    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    ImVec2 pos = ImGui::GetCursorScreenPos();
    ImVec2 size = ImGui::GetContentRegionAvail();
    draw_list->AddRectFilled(pos, ImVec2(pos.x + size.x, pos.y + size.y), ImGui::GetColorU32(bg_color));

    
    for (const auto& msg : global_console_out) {
    
        if (msg.log_type == CONSOLE_ERROR_LOG)
            crnt_color = error_text_color;
        else if (msg.log_type == CONSOLE_WARNING_LOG)
            crnt_color = warning_text_color;
        else
            crnt_color = ImVec4(1.0, 1.0, 1.0, 1.0);

        ImGui::PushStyleColor(ImGuiCol_Text, crnt_color);
        ImGui::TextColored(crnt_color, msg.log.c_str());
        ImGui::PopStyleColor();
    
    }
    
   

    ImGui::EndChild();
	ImGui::End();
}
