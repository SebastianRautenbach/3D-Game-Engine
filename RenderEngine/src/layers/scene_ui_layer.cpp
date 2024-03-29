#include "layers/scene_ui_layer.h"

wizm::scene_ui_layer::scene_ui_layer(core_scene* scene)
	:core_layer("scene ui layer"), m_scene(scene)
{
}

wizm::scene_ui_layer::~scene_ui_layer()
{
}

void wizm::scene_ui_layer::OnAttach()
{
}

void wizm::scene_ui_layer::OnDetach()
{
}

void wizm::scene_ui_layer::update()
{
	ImGui::Begin("scene view");


	for (auto ents : m_scene->m_entities)
	{
		ImGui::Text("Pos:");
		
		float pos[3] = { ents->m_position.x, ents->m_position .y, ents->m_position.z};
		std::string trans_id = ents->m_ent_ID + "pos";
		ImGui::DragFloat3(trans_id.c_str(), pos, 0.1);
		ents->set_position(glm::vec3(pos[0], pos[1], pos[2]));

		ImGui::Text("Rot:");
		float rot[3] = { ents->m_rotation.x, ents->m_rotation.y, ents->m_rotation.z };
		trans_id = ents->m_ent_ID + "rot";
		ImGui::DragFloat3(trans_id.c_str(), rot, 0.1);
		ents->set_rotation(glm::vec3(rot[0], rot[1], rot[2]));

		ImGui::Text("-------------------------------------");
	}

	ImGui::End();
}
