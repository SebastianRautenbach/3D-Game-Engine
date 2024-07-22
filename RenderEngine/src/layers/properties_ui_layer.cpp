#include "layers/properties_ui_layer.h"
#include "other utils/strconvr.h"

wizm::properties_ui_layer::properties_ui_layer(core_scene* scene, gl_renderer* renderer, asset_manager* manager)
	:m_scene(scene), m_renderer(renderer), m_asset_manager(manager)
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

void wizm::properties_ui_layer::update(float delta_time)
{
	ImGui::Begin("Properties");
	
	if (m_scene->get_crnt_entity() != nullptr)
	{
		auto select_ent = m_scene->get_crnt_entity();
		ImGui::Text(select_ent->m_ent_ID.c_str());


		std::string trans_id;


		
		

		ImGui::Text("Position:");
		
		{
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
			float pos[3] = { select_ent->get_position().x, select_ent->get_position().y, select_ent->get_position().z };
			ImVec2 buttonSize = ImVec2(ImGui::CalcTextSize(" X ").x, ImGui::GetFrameHeight());
			float dragWidth = 100.0f;
			



			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f }); ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f }); ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
			trans_id = "##" + select_ent->m_ent_ID + "posX";
			ImGui::Button("X", buttonSize);
			ImGui::SameLine();
			ImGui::SetNextItemWidth(dragWidth);
			if (ImGui::DragFloat(trans_id.c_str(), &pos[0], .01f, 0.0f, 0.0f, "%.2f", ImGuiSliderFlags_NoRoundToFormat))
				select_ent->set_position(glm::vec3(pos[0], pos[1], pos[2]));
			ImGui::PopStyleColor(3);



			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.3f, 1.0f }); ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f }); ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
			trans_id = "##" + select_ent->m_ent_ID + "posY";
			ImGui::SameLine();
			ImGui::Button("Y", buttonSize);
			ImGui::SameLine();
			ImGui::SetNextItemWidth(dragWidth);
			if (ImGui::DragFloat(trans_id.c_str(), &pos[1], .01f, 0.0f, 0.0f, "%.2f", ImGuiSliderFlags_NoRoundToFormat))
				select_ent->set_position(glm::vec3(pos[0], pos[1], pos[2]));
			ImGui::PopStyleColor(3);




			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.4f, 0.8f, 1.0f }); ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.5f, 0.9f, 1.0f }); ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.4f, 0.8f, 1.0f });
			trans_id = "##" + select_ent->m_ent_ID + "posZ";
			ImGui::SameLine();
			ImGui::Button("Z", buttonSize);
			ImGui::SameLine();
			ImGui::SetNextItemWidth(dragWidth);
			if (ImGui::DragFloat(trans_id.c_str(), &pos[2], .01f, 0.0f, 0.0f, "%.2f", ImGuiSliderFlags_NoRoundToFormat))
				select_ent->set_position(glm::vec3(pos[0], pos[1], pos[2]));
			ImGui::PopStyleColor(3);

			ImGui::PopStyleVar();
		}


		ImGui::Text("Rotation:");
		{
			

			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
			float rot[3] = { select_ent->get_rotation().x, select_ent->get_rotation().y, select_ent->get_rotation().z };
			ImVec2 buttonSize = ImVec2(ImGui::CalcTextSize(" X ").x, ImGui::GetFrameHeight());
			float dragWidth = 100.0f;

			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f }); ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f }); ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
			trans_id = "##" + select_ent->m_ent_ID + "rotX";
			ImGui::Button("P", buttonSize);
			ImGui::SameLine();
			ImGui::SetNextItemWidth(dragWidth);
			if (ImGui::DragFloat(trans_id.c_str(), &rot[0], .01f, 0.0f, 0.0f, "%.2f", ImGuiSliderFlags_NoRoundToFormat))
				select_ent->set_rotation(glm::vec3(rot[0], rot[1], rot[2]));
			ImGui::PopStyleColor(3);

			
			
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.3f, 1.0f }); ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f }); ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
			trans_id = "##" + select_ent->m_ent_ID + "rotY";
			ImGui::SameLine();
			ImGui::Button("Y", buttonSize);
			ImGui::SameLine();
			ImGui::SetNextItemWidth(dragWidth);
			if (ImGui::DragFloat(trans_id.c_str(), &rot[1], .01f, 0.0f, 0.0f, "%.2f", ImGuiSliderFlags_NoRoundToFormat))
				select_ent->set_rotation(glm::vec3(rot[0], rot[1], rot[2]));
			ImGui::PopStyleColor(3);


			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.4f, 0.8f, 1.0f }); ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.5f, 0.9f, 1.0f }); ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.4f, 0.8f, 1.0f });
			trans_id = "##" + select_ent->m_ent_ID + "rotZ";
			ImGui::SameLine();
			ImGui::Button("R", buttonSize);
			ImGui::SameLine();
			ImGui::SetNextItemWidth(dragWidth);
			if (ImGui::DragFloat(trans_id.c_str(), &rot[2], .01f, 0.0f, 0.0f, "%.2f", ImGuiSliderFlags_NoRoundToFormat))
				select_ent->set_rotation(glm::vec3(rot[0], rot[1], rot[2]));
			ImGui::PopStyleColor(3);

			
			ImGui::PopStyleVar();
		}

		ImGui::Text("Scale:");

		{
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
			float sca[3] = { select_ent->get_scale().x, select_ent->get_scale().y, select_ent->get_scale().z };
			ImVec2 buttonSize = ImVec2(ImGui::CalcTextSize(" X ").x, ImGui::GetFrameHeight());
			float dragWidth = 100.0f;



			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f }); ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f }); ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
			trans_id = "##" + select_ent->m_ent_ID + "scaX";
			ImGui::Button("X", buttonSize);
			ImGui::SameLine();
			ImGui::SetNextItemWidth(dragWidth);
			if (ImGui::DragFloat(trans_id.c_str(), &sca[0], .01f, 0.0f, 0.0f, "%.2f", ImGuiSliderFlags_NoRoundToFormat))
				select_ent->set_scale(glm::vec3(sca[0], sca[1], sca[2]));
			ImGui::PopStyleColor(3);


			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.3f, 1.0f }); ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f }); ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
			trans_id = "##" + select_ent->m_ent_ID + "scaY";
			ImGui::SameLine();
			ImGui::Button("Y", buttonSize);
			ImGui::SameLine();
			ImGui::SetNextItemWidth(dragWidth);
			if (ImGui::DragFloat(trans_id.c_str(), &sca[1], .01f, 0.0f, 0.0f, "%.2f", ImGuiSliderFlags_NoRoundToFormat))
				select_ent->set_scale(glm::vec3(sca[0], sca[1], sca[2]));
			ImGui::PopStyleColor(3);



			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.4f, 0.8f, 1.0f }); ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.5f, 0.9f, 1.0f }); ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.4f, 0.8f, 1.0f });
			trans_id = "##" + select_ent->m_ent_ID + "scaZ";
			ImGui::SameLine();
			ImGui::Button("Z", buttonSize);
			ImGui::SameLine();
			ImGui::SetNextItemWidth(dragWidth);
			if (ImGui::DragFloat(trans_id.c_str(), &sca[2], .01f, 0.0f, 0.0f, "%.2f", ImGuiSliderFlags_NoRoundToFormat))
				select_ent->set_scale(glm::vec3(sca[0], sca[1], sca[2]));
			ImGui::PopStyleColor(3);

			ImGui::PopStyleVar();
		}



		

		ImGui::Text("Components");
		ImGui::Separator();

		for (int i = 0; i < select_ent->m_components_list.size(); i++)
		{
			auto comps = select_ent->m_components_list[i];


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


			trans_id = comp_type + "##" + select_ent->m_ent_ID + std::to_string(comps->m_component_type) + std::to_string(i);
			if (ImGui::CollapsingHeader(trans_id.c_str()))
			{
				trans_id = "transfrom ##" + select_ent->m_ent_ID + std::to_string(comps->m_component_type) + std::to_string(i);
				ImGui::Indent(20.0f);
				if (ImGui::CollapsingHeader("transform"))
				{

					ImGui::Text("Position:");
					float pos[3] = { comps->get_position().x, comps->get_position().y, comps->get_position().z };
					std::string trans_id = select_ent->m_ent_ID + "c pos" + std::to_string(comps->m_component_type) + std::to_string(i);
					if (ImGui::DragFloat3(trans_id.c_str(), pos, 0.01))
						comps->set_position(glm::vec3(pos[0], pos[1], pos[2]));

					ImGui::Text("Rotation:");
					float rot[3] = { comps->get_rotation().x, comps->get_rotation().y, comps->get_rotation().z };
					trans_id = select_ent->m_ent_ID + "c rot" + std::to_string(comps->m_component_type) + std::to_string(i);
					if (ImGui::DragFloat3(trans_id.c_str(), rot, 0.1))
						comps->set_rotation(glm::vec3(rot[0], rot[1], rot[2]));


					ImGui::Text("Scale:");
					float sca[3] = { comps->get_scale().x, comps->get_scale().y, comps->get_scale().z };
					trans_id = select_ent->m_ent_ID + "c sca" + std::to_string(comps->m_component_type) + std::to_string(i);
					if (ImGui::DragFloat3(trans_id.c_str(), sca, 0.01))
						comps->set_scale(glm::vec3(sca[0], sca[1], sca[2]));


				}



				ImGui::Unindent(20.0f);


				modify_component_attrib(comp_type, comps);



			}
			if (ImGui::IsItemClicked(1))
			{
				ImGui::OpenPopup("ModComp");
				m_scene->get_crnt_entity()->set_selected_comp(comps);
			}

		}

		

		if (ImGui::BeginPopup("ModComp")) {
			ImGui::Text("Modify Component");
			ImGui::Separator();

			if (ImGui::MenuItem("Delete")) {

				select_ent->m_components_list.erase(std::find(select_ent->m_components_list.begin(),
					select_ent->m_components_list.end(), m_scene->get_crnt_entity()->get_selected_comp()));

				
			}

			ImGui::EndPopup();
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
			
			//test 
			for (const auto& i : m_scene->m_entities)
			{
				for (auto y : i->m_components_list)
				{
					auto staticmesh = std::dynamic_pointer_cast<staticmesh_component>(y);
					if(staticmesh)
					{
						//auto new_mesh = staticmesh->copy();
						//select_ent->add_component(new_mesh);
					}
				}
			}
			
			
			
		}
		if (ImGui::MenuItem("Point Light")) {
			select_ent->add_component(std::make_shared<pointlight_component>());
			
		}
		if (ImGui::MenuItem("Spot Light")) {
			
		}
		if (ImGui::MenuItem("Directional Light")) {
			select_ent->add_component(std::make_shared<directionallight_component>());
			
		}
		if (ImGui::MenuItem("Sound")) {
			
		}

		ImGui::EndPopup();
	}
}

void wizm::properties_ui_layer::modify_component_attrib(std::string& type, std::shared_ptr<core_component> component)
{
	auto select_ent = m_scene->get_crnt_entity();
	std::string trans_id;
	if (type == "PointLight")
	{
		trans_id = "Radius ##" + select_ent->m_ent_ID + std::to_string(component->m_component_type);
		auto pointlight = std::dynamic_pointer_cast<pointlight_component>(component);

		ImGui::InputFloat(trans_id.c_str(), &pointlight->m_radius);

		float test[3] = { pointlight->m_diffuse.x, pointlight->m_diffuse.y, pointlight->m_diffuse.z };

		ImGui::ColorPicker3("test", test);
		pointlight->m_diffuse = glm::vec3(test[0], test[1], test[2]);
	}


	if (type == "DirectionalLight")
	{
		auto directionallight = std::dynamic_pointer_cast<directionallight_component>(component);

		float test[3] = { directionallight->m_ambient.x, directionallight->m_ambient.y, directionallight->m_ambient.z };

		ImGui::ColorPicker3("test", test);
		directionallight->m_ambient = glm::vec3(test[0], test[1], test[2]);
	}


	if (type == "StaticMesh")
	{
		auto staticmesh = std::dynamic_pointer_cast<staticmesh_component>(component);
		
		ImGui::Button("change mesh", ImVec2(125, 125));
		if (ImGui::BeginDragDropTarget()) {
		
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM")) {

				const wchar_t* id = (const wchar_t*)payload->Data;

				
				staticmesh->m_asset_id = wstring_to_string(id);
				m_asset_manager->assign_assets();
				m_scene->m_reloaded = true;
			}

			ImGui::EndDragDropTarget();
		}
		
	}
}
