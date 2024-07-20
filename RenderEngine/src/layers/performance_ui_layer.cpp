#include "layers/performance_ui_layer.h"

wizm::performace_ui_layer::performace_ui_layer(core_scene* scene)
	:core_layer("performance layer"), m_scene(scene)
{
}

wizm::performace_ui_layer::~performace_ui_layer()
{
}

void wizm::performace_ui_layer::OnAttach()
{
}

void wizm::performace_ui_layer::OnDetach()
{
}

void wizm::performace_ui_layer::update(float delta_time)
{
	ImGui::Begin("Performance");
	ImGuiIO& io = ImGui::GetIO();
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
	
	ImGui::End();
}
