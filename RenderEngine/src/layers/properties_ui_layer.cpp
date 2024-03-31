#include "layers/properties_ui_layer.h"

wizm::properties_ui_layer::properties_ui_layer(core_scene* scene)
	:m_scene(scene)
{
}

wizm::properties_ui_layer::~properties_ui_layer()
{
}

void wizm::properties_ui_layer::OnAttach()
{
}

void wizm::properties_ui_layer::OnDetach()
{
}

void wizm::properties_ui_layer::update()
{
	ImGui::Begin("Properties");
	
	if (m_scene->get_crnt_entity() != nullptr)
	{
		auto select_ent = m_scene->get_crnt_entity();
		ImGui::Text(select_ent->m_ent_ID.c_str());


		std::string trans_id;
		ImGui::Text("Position:");
		float pos[3] = { select_ent->m_position.x, select_ent->m_position.y, select_ent->m_position.z };
		trans_id = select_ent->m_ent_ID + "pos";
		ImGui::DragFloat3(trans_id.c_str(), pos, 0.01);
		select_ent->set_position(glm::vec3(pos[0], pos[1], pos[2]));

		ImGui::Text("Rotation:");
		float rot[3] = { select_ent->m_rotation.x, select_ent->m_rotation.y, select_ent->m_rotation.z };
		trans_id = select_ent->m_ent_ID + "rot";
		ImGui::DragFloat3(trans_id.c_str(), rot, 0.01);
		select_ent->set_rotation(glm::vec3(rot[0], rot[1], rot[2]));


		ImGui::Text("Scale:");
		float sca[3] = { select_ent->m_scale.x, select_ent->m_scale.y, select_ent->m_scale.z };
		trans_id = select_ent->m_ent_ID + "sca";
		ImGui::DragFloat3(trans_id.c_str(), sca, 0.01);
		select_ent->set_scale(glm::vec3(sca[0], sca[1], sca[2]));





		ImGui::Text("Components");
		ImGui::Separator();


		for (auto comps : select_ent->m_components_list)
		{
			std::string comp_type;

			switch (comps->m_component_type)
			{
			case ePointLight:
				comp_type = "PointLight";
				break;
			case eStaticMesh:
				comp_type = "StaticMesh";
				break;
			case eDirectionalLight:
				comp_type = "DirectionalLight";
				break;

			default:
				break;
			}

			

			trans_id = comp_type + "##" + select_ent->m_ent_ID + std::to_string(comps->m_component_type);
			if (ImGui::CollapsingHeader(trans_id.c_str()))
			{
				trans_id = "transfrom ##" + select_ent->m_ent_ID + std::to_string(comps->m_component_type);
				ImGui::Indent(20.0f);
				if (ImGui::CollapsingHeader("transform"))
				{

					ImGui::Text("Position:");
					float pos[3] = { comps->m_position.x, comps->m_position.y, comps->m_position.z };
					std::string trans_id = select_ent->m_ent_ID + "c pos" + std::to_string(comps->m_component_type);
					ImGui::DragFloat3(trans_id.c_str(), pos, 0.01);
					comps->set_local_position(glm::vec3(pos[0], pos[1], pos[2]));

					ImGui::Text("Rotation:");
					float rot[3] = { comps->m_rotation.x, comps->m_rotation.y, comps->m_rotation.z };
					trans_id = select_ent->m_ent_ID + "c rot" + std::to_string(comps->m_component_type);
					ImGui::DragFloat3(trans_id.c_str(), rot, 0.01);
					comps->set_local_rotation(glm::vec3(rot[0], rot[1], rot[2]));


					ImGui::Text("Scale:");
					float sca[3] = { comps->m_scale.x, comps->m_scale.y, comps->m_scale.z };
					trans_id = select_ent->m_ent_ID + "c sca" + std::to_string(comps->m_component_type);
					ImGui::DragFloat3(trans_id.c_str(), sca, 0.01);
					comps->set_local_scale(glm::vec3(sca[0], sca[1], sca[2]));
				}
				ImGui::Unindent(20.0f);

				if (comp_type == "PointLight")
				{
					trans_id = "Radius ##" + select_ent->m_ent_ID + std::to_string(comps->m_component_type);
					auto pointlight = std::dynamic_pointer_cast<pointlight_component>(comps);
					ImGui::InputFloat(trans_id.c_str(), &pointlight->m_radius);
				}

			}

		}

	}

	ImGui::End();
}
