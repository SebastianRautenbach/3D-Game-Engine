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

/*


				THIS IS ONLY TESTING PURPOSES

*/

void wizm::scene_ui_layer::update()
{
	static bool add_ent = false;

	ImGui::Begin("scene view");


	
	for (auto ents : m_scene->m_entities)
	{
		if (ImGui::Button(ents->m_ent_ID.c_str()))
		{
			ImGui::OpenPopup("ModEnt");
			m_scene->set_crnt_entity(ents);
		}
	}


	if (ImGui::BeginPopup("ModEnt")) {
		ImGui::Text("Modify Entity");
		ImGui::Separator();

		if (ImGui::MenuItem("Rename")) {
			
		}
		if (ImGui::MenuItem("Delete")) {
			m_scene->m_entities.erase(std::find(m_scene->m_entities.begin(), m_scene->m_entities.end(), m_scene->get_crnt_entity()));
			for (auto ents : m_scene->m_entities)
				m_scene->set_crnt_entity(ents);
		}

		ImGui::EndPopup();
	}






	//---------------------------------------------------------------------------------------------------------
	
	if (ImGui::Button("Add Entity"))
		ImGui::OpenPopup("AddEntityPopup");

	if (ImGui::BeginPopup("AddEntityPopup")) {
		ImGui::Text("Add Entity");
		ImGui::Separator();
		
		static char enity_name[128] = "Component Name";
	
		if (ImGui::IsPopupOpen("AddEntityPopup")) {
			ImGui::SetKeyboardFocusHere(0);
		}


		if (ImGui::InputText("##name", enity_name, IM_ARRAYSIZE(enity_name))) {}
		
		if (ImGui::MenuItem("Add Entity")) {
			std::string _ent_str;
			_ent_str = enity_name;
			bool does_ent_name_exist = false;
			for (const auto y : m_scene->m_entities)
			{
				if (_ent_str == y->m_ent_ID)
				{
					does_ent_name_exist = true;
					break;
				}
			}
			if (!does_ent_name_exist)
			{
				m_scene->add_entity(_ent_str);
			}
		}
		
		ImGui::EndPopup();
	}



	



	ImGui::End();
}
