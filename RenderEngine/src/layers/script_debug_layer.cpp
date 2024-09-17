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
	ImGui::TextColored(ImVec4(1, 0, 0, 1), global_console_out.c_str());
	ImGui::End();
}
