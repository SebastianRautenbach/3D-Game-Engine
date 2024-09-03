#include "layers/scene_viewport_layer.h"

wizm::scene_viewport_layer::scene_viewport_layer(std::shared_ptr<camera_manager> camera_manager)	
	:core_layer("scene_viewport_layer"), m_camera_manager(camera_manager)
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
	if(!m_camera_manager->m_crnt_camera)
		ImGui::Text("No Camera in Scene found!");
	ImGui::End();
}
