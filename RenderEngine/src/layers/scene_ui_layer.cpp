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
			if (ImGui::CollapsingHeader(ents->m_ent_ID.c_str()))
			{
				m_scene->set_crnt_entity(ents);

				



				

			}
		}
	if (!add_ent) {
		if (ImGui::Button("+##add_ent")) {

			add_ent = true;
		}
	}
	
	else {
		ImGui::Begin("add entity");

		ImGui::Text("Name enitity");
		static char ent_name[255] = "Enter name";
		std::string _ent_str;
		ImGui::InputText("##ENTNAME", ent_name, 255);
		_ent_str = ent_name;
		if (ImGui::Button("Add Entity") && !_ent_str.empty())
		{
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
				add_ent = false;
			}
		}
		ImGui::SameLine();
		if (ImGui::Button("Cancel"))
		{
			add_ent = false;
		}


		ImGui::End();
	}

	ImGui::End();
}
