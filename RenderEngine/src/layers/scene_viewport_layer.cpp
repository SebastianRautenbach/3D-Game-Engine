#include "layers/scene_viewport_layer.h"

wizm::scene_viewport_layer::scene_viewport_layer()
	:core_layer("scene_viewport_layer")
{
}

wizm::scene_viewport_layer::~scene_viewport_layer()
{
}

void wizm::scene_viewport_layer::OnAttach()
{
}

void wizm::scene_viewport_layer::OnDetach()
{
}

void wizm::scene_viewport_layer::update(float delta_time)
{
	ImGui::Begin("Scene Viewport");
	ImGui::Text("No Camera in Scene found!");
	ImGui::End();
}
