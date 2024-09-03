#include "layers/scene_ui_layer.h"

wizm::scene_ui_layer::scene_ui_layer(core_scene* scene, gl_renderer* renderer)
	:core_layer("scene ui layer"), m_scene(scene), m_renderer(renderer)
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

void wizm::scene_ui_layer::update(float delta_time)
{
	static bool add_ent = false;

	ImGui::Begin("scene view");

	if (ImGui::Button("Add Entity"))
		ImGui::OpenPopup("AddEntityPopup");

	for (auto ents : m_scene->m_entities)
	{
		if (ImGui::TreeNodeEx(ents->m_ent_ID.c_str(), 
			ImGuiTreeNodeFlags_OpenOnArrow 
			| ImGuiTreeNodeFlags_OpenOnDoubleClick 
			| ImGuiTreeNodeFlags_SpanAvailWidth)) 
		{
			
			// open next list _>> BLAH BLAH
			ImGui::TreePop();
		}
		if (ImGui::IsItemClicked(ImGuiMouseButton_Right))
		{
			m_scene->set_crnt_entity(ents);
			ImGui::OpenPopup("ModEnt");
		}
		if (ImGui::IsItemClicked())
		{
			m_scene->set_crnt_entity(ents);
		}

	}


	if (ImGui::BeginPopup("ModEnt")) {
		ImGui::Text("Modify Entity");
		ImGui::Separator();
		
		
		char entity_name[256];
		strncpy_s(entity_name, sizeof(entity_name), m_scene->get_crnt_entity()->m_ent_ID.c_str(), _TRUNCATE);



		if (ImGui::InputText("##name", entity_name, IM_ARRAYSIZE(entity_name)))
			m_scene->get_crnt_entity()->m_ent_ID = entity_name;


		if (ImGui::MenuItem("Delete")) {
			m_scene->m_entities.erase(std::find(m_scene->m_entities.begin(), m_scene->m_entities.end(), m_scene->get_crnt_entity()));
			
			m_renderer->update_draw_data();
			
			for (auto ents : m_scene->m_entities)
				m_scene->set_crnt_entity(ents);
			
			if (m_scene->m_entities.empty())
				m_scene->set_crnt_entity(nullptr);
		}
		if (ImGui::MenuItem("Duplicate")) {
			
			auto name = m_scene->get_crnt_entity()->m_ent_ID;
			
			while (m_scene->does_ent_name_exist(name)) {
				name += "(1)";
			}
			

			auto crnt = m_scene->get_crnt_entity()->copy_(name);
			m_scene->add_entity(crnt);
			m_scene->set_crnt_entity(crnt);
		}

		ImGui::EndPopup();
	}

	//---------------------------------------------------------------------------------------------------------


	ImGui::Separator();


	//---------------------------------------------------------------------------------------------------------
	
	
	

	if (ImGui::BeginPopup("AddEntityPopup")) {
		ImGui::Text("Add Entity");
		ImGui::Separator();
		
		static char enity_name[128] = "Entity Name";
	
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
