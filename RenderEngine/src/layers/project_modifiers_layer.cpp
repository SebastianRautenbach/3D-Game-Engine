#include "layers/project_modifiers_layer.h"
#include "scene.h"

wizm::project_modifier::project_modifier(core_scene* scene)
	:m_scene(scene)
{
}

wizm::project_modifier::~project_modifier()
{
}

void wizm::project_modifier::OnAttach()
{
}

void wizm::project_modifier::OnDetach()
{
}

void wizm::project_modifier::update(float delta_time)
{
	ImGui::Begin("file");


	if (ImGui::Button("Save")) {
		m_scene->save_map_data();
	}

	if (ImGui::Button("read")) {
		m_scene->read_map_data();
	}

	ImGui::End();
}
