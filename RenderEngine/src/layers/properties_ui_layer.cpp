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
		ImGui::Text(m_scene->get_crnt_entity()->m_ent_ID.c_str());


		std::string trans_id;


		
		

		ImGui::Text("Position:");
		
		{
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
			float pos[3] = { m_scene->get_crnt_entity()->get_position().x, m_scene->get_crnt_entity()->get_position().y, m_scene->get_crnt_entity()->get_position().z };
			ImVec2 buttonSize = ImVec2(ImGui::CalcTextSize(" X ").x, ImGui::GetFrameHeight());
			float dragWidth = 100.0f;
			



			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f }); ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f }); ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
			trans_id = "##" + m_scene->get_crnt_entity()->m_ent_ID + "posX";
			ImGui::Button("X", buttonSize);
			ImGui::SameLine();
			ImGui::SetNextItemWidth(dragWidth);
			if (ImGui::DragFloat(trans_id.c_str(), &pos[0], .01f, 0.0f, 0.0f, "%.2f", ImGuiSliderFlags_NoRoundToFormat))
				m_scene->get_crnt_entity()->set_position(glm::vec3(pos[0], pos[1], pos[2]));
			ImGui::PopStyleColor(3);



			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.3f, 1.0f }); ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f }); ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
			trans_id = "##" + m_scene->get_crnt_entity()->m_ent_ID + "posY";
			ImGui::SameLine();
			ImGui::Button("Y", buttonSize);
			ImGui::SameLine();
			ImGui::SetNextItemWidth(dragWidth);
			if (ImGui::DragFloat(trans_id.c_str(), &pos[1], .01f, 0.0f, 0.0f, "%.2f", ImGuiSliderFlags_NoRoundToFormat))
				m_scene->get_crnt_entity()->set_position(glm::vec3(pos[0], pos[1], pos[2]));
			ImGui::PopStyleColor(3);




			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.4f, 0.8f, 1.0f }); ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.5f, 0.9f, 1.0f }); ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.4f, 0.8f, 1.0f });
			trans_id = "##" + m_scene->get_crnt_entity()->m_ent_ID + "posZ";
			ImGui::SameLine();
			ImGui::Button("Z", buttonSize);
			ImGui::SameLine();
			ImGui::SetNextItemWidth(dragWidth);
			if (ImGui::DragFloat(trans_id.c_str(), &pos[2], .01f, 0.0f, 0.0f, "%.2f", ImGuiSliderFlags_NoRoundToFormat))
				m_scene->get_crnt_entity()->set_position(glm::vec3(pos[0], pos[1], pos[2]));
			ImGui::PopStyleColor(3);

			ImGui::PopStyleVar();
		}


		ImGui::Text("Rotation:");
		{
			

			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
			float rot[3] = { m_scene->get_crnt_entity()->get_rotation().x, m_scene->get_crnt_entity()->get_rotation().y, m_scene->get_crnt_entity()->get_rotation().z };
			ImVec2 buttonSize = ImVec2(ImGui::CalcTextSize(" X ").x, ImGui::GetFrameHeight());
			float dragWidth = 100.0f;

			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f }); ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f }); ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
			trans_id = "##" + m_scene->get_crnt_entity()->m_ent_ID + "rotX";
			ImGui::Button("P", buttonSize);
			ImGui::SameLine();
			ImGui::SetNextItemWidth(dragWidth);
			if (ImGui::DragFloat(trans_id.c_str(), &rot[0], .01f, 0.0f, 0.0f, "%.2f", ImGuiSliderFlags_NoRoundToFormat))
				m_scene->get_crnt_entity()->set_rotation(glm::vec3(rot[0], rot[1], rot[2]));
			ImGui::PopStyleColor(3);

			
			
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.3f, 1.0f }); ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f }); ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
			trans_id = "##" + m_scene->get_crnt_entity()->m_ent_ID + "rotY";
			ImGui::SameLine();
			ImGui::Button("Y", buttonSize);
			ImGui::SameLine();
			ImGui::SetNextItemWidth(dragWidth);
			if (ImGui::DragFloat(trans_id.c_str(), &rot[1], .01f, 0.0f, 0.0f, "%.2f", ImGuiSliderFlags_NoRoundToFormat))
				m_scene->get_crnt_entity()->set_rotation(glm::vec3(rot[0], rot[1], rot[2]));
			ImGui::PopStyleColor(3);


			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.4f, 0.8f, 1.0f }); ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.5f, 0.9f, 1.0f }); ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.4f, 0.8f, 1.0f });
			trans_id = "##" + m_scene->get_crnt_entity()->m_ent_ID + "rotZ";
			ImGui::SameLine();
			ImGui::Button("R", buttonSize);
			ImGui::SameLine();
			ImGui::SetNextItemWidth(dragWidth);
			if (ImGui::DragFloat(trans_id.c_str(), &rot[2], .01f, 0.0f, 0.0f, "%.2f", ImGuiSliderFlags_NoRoundToFormat))
				m_scene->get_crnt_entity()->set_rotation(glm::vec3(rot[0], rot[1], rot[2]));
			ImGui::PopStyleColor(3);

			
			ImGui::PopStyleVar();
		}

		ImGui::Text("Scale:");

		{
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
			float sca[3] = { m_scene->get_crnt_entity()->get_scale().x, m_scene->get_crnt_entity()->get_scale().y, m_scene->get_crnt_entity()->get_scale().z };
			ImVec2 buttonSize = ImVec2(ImGui::CalcTextSize(" X ").x, ImGui::GetFrameHeight());
			float dragWidth = 100.0f;



			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f }); ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f }); ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
			trans_id = "##" + m_scene->get_crnt_entity()->m_ent_ID + "scaX";
			ImGui::Button("X", buttonSize);
			ImGui::SameLine();
			ImGui::SetNextItemWidth(dragWidth);
			if (ImGui::DragFloat(trans_id.c_str(), &sca[0], .01f, 0.0f, 0.0f, "%.2f", ImGuiSliderFlags_NoRoundToFormat))
				m_scene->get_crnt_entity()->set_scale(glm::vec3(sca[0], sca[1], sca[2]));
			ImGui::PopStyleColor(3);


			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.3f, 1.0f }); ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f }); ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
			trans_id = "##" + m_scene->get_crnt_entity()->m_ent_ID + "scaY";
			ImGui::SameLine();
			ImGui::Button("Y", buttonSize);
			ImGui::SameLine();
			ImGui::SetNextItemWidth(dragWidth);
			if (ImGui::DragFloat(trans_id.c_str(), &sca[1], .01f, 0.0f, 0.0f, "%.2f", ImGuiSliderFlags_NoRoundToFormat))
				m_scene->get_crnt_entity()->set_scale(glm::vec3(sca[0], sca[1], sca[2]));
			ImGui::PopStyleColor(3);



			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.4f, 0.8f, 1.0f }); ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.5f, 0.9f, 1.0f }); ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.4f, 0.8f, 1.0f });
			trans_id = "##" + m_scene->get_crnt_entity()->m_ent_ID + "scaZ";
			ImGui::SameLine();
			ImGui::Button("Z", buttonSize);
			ImGui::SameLine();
			ImGui::SetNextItemWidth(dragWidth);
			if (ImGui::DragFloat(trans_id.c_str(), &sca[2], .01f, 0.0f, 0.0f, "%.2f", ImGuiSliderFlags_NoRoundToFormat))
				m_scene->get_crnt_entity()->set_scale(glm::vec3(sca[0], sca[1], sca[2]));
			ImGui::PopStyleColor(3);

			ImGui::PopStyleVar();
		}



		

		ImGui::Text("Components");
		ImGui::Separator();

		for (int i = 0; i < m_scene->get_crnt_entity()->m_components_list.size(); i++)
		{
			auto& comps = m_scene->get_crnt_entity()->m_components_list[i];


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
			case eSpotLight:
				comp_type = "SpotLight";
				break;

			default:
				break;
			}


			trans_id = comp_type + "##" + m_scene->get_crnt_entity()->m_ent_ID + std::to_string(comps->m_component_type) + std::to_string(i);
			if (ImGui::CollapsingHeader(trans_id.c_str()))
			{
				trans_id = "transfrom ##" + m_scene->get_crnt_entity()->m_ent_ID + std::to_string(comps->m_component_type) + std::to_string(i);
				ImGui::Indent(20.0f);
				if (ImGui::CollapsingHeader("transform"))
				{

					ImGui::Text("Position:");
					float pos[3] = { comps->get_position().x, comps->get_position().y, comps->get_position().z };
					std::string trans_id = m_scene->get_crnt_entity()->m_ent_ID + "c pos" + std::to_string(comps->m_component_type) + std::to_string(i);
					if (ImGui::DragFloat3(trans_id.c_str(), pos, 0.01))
						comps->set_position(glm::vec3(pos[0], pos[1], pos[2]));

					ImGui::Text("Rotation:");
					float rot[3] = { comps->get_rotation().x, comps->get_rotation().y, comps->get_rotation().z };
					trans_id = m_scene->get_crnt_entity()->m_ent_ID + "c rot" + std::to_string(comps->m_component_type) + std::to_string(i);
					if (ImGui::DragFloat3(trans_id.c_str(), rot, 0.1))
						comps->set_rotation(glm::vec3(rot[0], rot[1], rot[2]));


					ImGui::Text("Scale:");
					float sca[3] = { comps->get_scale().x, comps->get_scale().y, comps->get_scale().z };
					trans_id = m_scene->get_crnt_entity()->m_ent_ID + "c sca" + std::to_string(comps->m_component_type) + std::to_string(i);
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

				

				m_scene->get_crnt_entity()->m_components_list.erase(std::find(m_scene->get_crnt_entity()->m_components_list.begin(),
					m_scene->get_crnt_entity()->m_components_list.end(), m_scene->get_crnt_entity()->get_selected_comp()));
				m_scene->get_crnt_entity()->set_selected_comp(nullptr);
			}

			ImGui::EndPopup();
		}

		component_add_popup();

	}

	ImGui::End();
}

void wizm::properties_ui_layer::component_add_popup()
{
	if (ImGui::Button("Add Component")) {
		ImGui::OpenPopup("AddComponentPopup");
	}

	if (ImGui::BeginPopup("AddComponentPopup")) {
		ImGui::Text("Select Component to Add");
		ImGui::Separator();

		if (ImGui::MenuItem("Static Mesh")) {
			m_scene->get_crnt_entity()->add_component(std::make_shared<staticmesh_component>());
		}
		if (ImGui::MenuItem("Point Light")) {
			m_scene->get_crnt_entity()->add_component(std::make_shared<pointlight_component>());
			
		}
		if (ImGui::MenuItem("Spot Light")) {
			m_scene->get_crnt_entity()->add_component(std::make_shared<spotlight_component>());
		}
		if (ImGui::MenuItem("Directional Light")) {
			m_scene->get_crnt_entity()->add_component(std::make_shared<directionallight_component>());
			
		}
		if (ImGui::MenuItem("Sound")) {
			
		}
		if (ImGui::MenuItem("box volume")) {
			
			for (const auto& comp : m_scene->get_crnt_entity()->m_components_list) {
				auto sm_comp = std::dynamic_pointer_cast<staticmesh_component>(comp);
				if (sm_comp) {
					auto box = std::dynamic_pointer_cast<boxvolume>(m_scene->get_crnt_entity()->add_component(std::make_shared<boxvolume>(sm_comp->m_model->center, sm_comp->m_model->extents, sm_comp->m_model->axes)));
					box->m_shader = sm_comp->m_material->m_shader;
					break;
				}
			}

			
		}

		ImGui::EndPopup();
	}
}

void wizm::properties_ui_layer::modify_component_attrib(std::string& type, std::shared_ptr<core_component> component)
{
	std::string trans_id;
	if (type == "PointLight")
	{
		trans_id = "Radius ##" + m_scene->get_crnt_entity()->m_ent_ID + std::to_string(component->m_component_type);
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

	if (type == "SpotLight")
	{
		auto spotlight = std::dynamic_pointer_cast<spotlight_component>(component);

		float ambient[3] = { spotlight->m_ambient.x, spotlight->m_ambient.y, spotlight->m_ambient.z };
		ImGui::ColorPicker3("Ambient", ambient);
		spotlight->m_ambient = glm::vec3(ambient[0], ambient[1], ambient[2]);

		float diffuse[3] = { spotlight->m_diffuse.x, spotlight->m_diffuse.y, spotlight->m_diffuse.z };
		ImGui::ColorPicker3("Diffuse", diffuse);
		spotlight->m_diffuse = glm::vec3(diffuse[0], diffuse[1], diffuse[2]);


		float specular[3] = { spotlight->m_specular.x, spotlight->m_specular.y, spotlight->m_specular.z };
		ImGui::ColorPicker3("Specular", specular);
		spotlight->m_specular = glm::vec3(specular[0], specular[1], specular[2]);

		ImGui::SliderFloat("Constant", &spotlight->m_constant, 0.0f, 10.0f, "%.3f");
		ImGui::SliderFloat("Linear", &spotlight->m_linear, 0.0f, 10.0f, "%.3f");
		ImGui::SliderFloat("Quadratic", &spotlight->m_quadratic, 0.0f, 10.0f, "%.3f");
		ImGui::InputFloat("Distance", &spotlight->m_distance,0.1f);

		float cutOffDeg = glm::degrees(glm::acos(spotlight->m_cutOff));
		float outerCutOffDeg = glm::degrees(glm::acos(spotlight->m_outerCutOff));

		ImGui::SliderFloat("CutOff Angle", &cutOffDeg, 0.0f, 90.0f, "%.1f");
		ImGui::SliderFloat("Outer CutOff Angle", &outerCutOffDeg, 0.0f, 90.0f, "%.1f");

		spotlight->m_cutOff = glm::cos(glm::radians(cutOffDeg));
		spotlight->m_outerCutOff = glm::cos(glm::radians(outerCutOffDeg));
	}


	if (type == "StaticMesh")
	{
		auto staticmesh = std::dynamic_pointer_cast<staticmesh_component>(component);
		
		ImGui::Text("Change Mesh");
		ImGui::Button("Drag and Drop", ImVec2(125, 125));
		if (ImGui::BeginDragDropTarget()) {
		
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM")) {

				const wchar_t* id = (const wchar_t*)payload->Data;

				if (m_asset_manager->get_asset_details_from_id(wstring_to_string(id)).type == tMESH)
				{
					staticmesh->m_asset_id = wstring_to_string(id);
					m_asset_manager->assign_assets();
					m_scene->m_reloaded = true;
				}
			}

			ImGui::EndDragDropTarget();
		}
		ImGui::Text("Change Diffuse Texture");
		ImGui::Button("Drag and Drop", ImVec2(125, 125));
		if (ImGui::BeginDragDropTarget()) {

			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM")) {

				const wchar_t* id = (const wchar_t*)payload->Data;

				if (m_asset_manager->get_asset_details_from_id(wstring_to_string(id)).type == tTEXTURE)
				{
					staticmesh->m_material->diffuse_asset_id = wstring_to_string(id);
					m_asset_manager->assign_assets();
					m_scene->m_reloaded = true;
				}
			}

			ImGui::EndDragDropTarget();
		}

		ImGui::Text("Change Specular Texture");
		ImGui::Button("Drag and Drop", ImVec2(125, 125));
		if (ImGui::BeginDragDropTarget()) {

			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM")) {

				const wchar_t* id = (const wchar_t*)payload->Data;

				if (m_asset_manager->get_asset_details_from_id(wstring_to_string(id)).type == tTEXTURE) {
					staticmesh->m_material->specular_asset_id = wstring_to_string(id);
					m_asset_manager->assign_assets();
					m_scene->m_reloaded = true;
				}
				
			}

			ImGui::EndDragDropTarget();
		}
		
	}
}
