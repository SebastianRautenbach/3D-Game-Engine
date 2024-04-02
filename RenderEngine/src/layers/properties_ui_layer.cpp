#include "layers/properties_ui_layer.h"

wizm::properties_ui_layer::properties_ui_layer(core_scene* scene, gl_renderer* renderer)
	:m_scene(scene), m_renderer(renderer)
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
		float pos[3] = { select_ent->get_position().x, select_ent->get_position().y, select_ent->get_position().z };
		trans_id = select_ent->m_ent_ID + "pos";
		if (ImGui::DragFloat3(trans_id.c_str(), pos, 0.01))
			select_ent->set_position(glm::vec3(pos[0], pos[1], pos[2]));

		ImGui::Text("Rotation:");
		float rot[3] = { select_ent->get_rotation().x, select_ent->get_rotation().y, select_ent->get_rotation().z };
		trans_id = select_ent->m_ent_ID + "rot";
		if (ImGui::DragFloat3(trans_id.c_str(), rot, 0.01))
			select_ent->set_rotation(glm::vec3(rot[0], rot[1], rot[2]));


		ImGui::Text("Scale:");
		float sca[3] = { select_ent->get_scale().x, select_ent->get_scale().y, select_ent->get_scale().z };
		trans_id = select_ent->m_ent_ID + "sca";
		if (ImGui::DragFloat3(trans_id.c_str(), sca, 0.01))
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
					float pos[3] = { comps->get_position().x, comps->get_position().y, comps->get_position().z};
					std::string trans_id = select_ent->m_ent_ID + "c pos" + std::to_string(comps->m_component_type);
					if(ImGui::DragFloat3(trans_id.c_str(), pos, 0.01))
						comps->set_position(glm::vec3(pos[0], pos[1], pos[2]));
					
					ImGui::Text("Rotation:");
					float rot[3] = { comps->get_rotation().x, comps->get_rotation().y, comps->get_rotation().z };
					trans_id = select_ent->m_ent_ID + "c rot" + std::to_string(comps->m_component_type);
					if(ImGui::DragFloat3(trans_id.c_str(), rot, 0.01))
						comps->set_rotation(glm::vec3(rot[0], rot[1], rot[2]));
					
					
					ImGui::Text("Scale:");
					float sca[3] = { comps->get_scale().x, comps->get_scale().y, comps->get_scale().z};
					trans_id = select_ent->m_ent_ID + "c sca" + std::to_string(comps->m_component_type);
					if(ImGui::DragFloat3(trans_id.c_str(), sca, 0.01))
						comps->set_scale(glm::vec3(sca[0], sca[1], sca[2]));


				}
				ImGui::Unindent(20.0f);

				if (comp_type == "PointLight")
				{
					trans_id = "Radius ##" + select_ent->m_ent_ID + std::to_string(comps->m_component_type);
					auto pointlight = std::dynamic_pointer_cast<pointlight_component>(comps);
					
					ImGui::InputFloat(trans_id.c_str(), &pointlight->m_radius);
					
					float test[3] = { pointlight->m_diffuse.x, pointlight->m_diffuse.y, pointlight->m_diffuse.z};
					
					ImGui::ColorPicker3("test", test);
					pointlight->m_diffuse = glm::vec3(test[0], test[1], test[2]);
				}


				if (comp_type == "DirectionalLight")
				{
					auto directionallight = std::dynamic_pointer_cast<directionallight_component>(comps);

					float test[3] = { directionallight->m_diffuse.x, directionallight->m_diffuse.y, directionallight->m_diffuse.z };

					ImGui::ColorPicker3("test", test);
					directionallight->m_diffuse = glm::vec3(test[0], test[1], test[2]);
				}
			}

		}



		component_add_popup(select_ent);

	}

	ImGui::End();
}

void wizm::properties_ui_layer::component_add_popup(core_entity* select_ent)
{
	if (ImGui::Button("Add Component")) {
		ImGui::OpenPopup("AddComponentPopup");
	}

	if (ImGui::BeginPopup("AddComponentPopup")) {
		ImGui::Text("Select Component to Add");
		ImGui::Separator();

		if (ImGui::MenuItem("Static Mesh")) {
			select_ent->add_component(std::make_shared<staticmesh_component>("resources/models/backpack.obj"));
			m_renderer->update_draw_data();
		}
		if (ImGui::MenuItem("Point Light")) {
			select_ent->add_component(std::make_shared<pointlight_component>());
			m_renderer->update_draw_data();
		}
		if (ImGui::MenuItem("Spot Light")) {
			
		}
		if (ImGui::MenuItem("Directional Light")) {
			select_ent->add_component(std::make_shared<directionallight_component>());
			m_renderer->update_draw_data();
		}
		if (ImGui::MenuItem("Sound")) {
			
		}

		ImGui::EndPopup();
	}
}
