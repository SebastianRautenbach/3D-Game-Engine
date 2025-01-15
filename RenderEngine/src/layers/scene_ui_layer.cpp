#include "layers/scene_ui_layer.h"
#include "system/scene_manager.h"
#include <functional>

wizm::scene_ui_layer::scene_ui_layer( gl_renderer* renderer)
	:core_layer("scene ui layer"), m_renderer(renderer)
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


void wizm::scene_ui_layer::update(float delta_time)
{
	static bool add_ent = false;

	ImGui::Begin("scene view");

	if (engine_status != EDITOR_STATUS) {
		ImGui::End();
		return;
	}

	if (ImGui::Button("Add Entity"))
		ImGui::OpenPopup("AddEntityPopup");

	for (auto ents : global_scene->m_entities) {
		std::function<void(core_entity*)> renderEntity = [&](core_entity* entity) {
			if (!entity) return;

		
			void* treeNodeId = (void*)((intptr_t)entity + std::hash<std::string>{}(entity->m_ent_ID));

		
			bool nodeOpen = ImGui::TreeNodeEx(treeNodeId,
				ImGuiTreeNodeFlags_OpenOnArrow |
				ImGuiTreeNodeFlags_SpanAvailWidth,
				"%s", entity->m_ent_ID.c_str());

		
			if (ImGui::IsItemClicked(ImGuiMouseButton_Left) || ImGui::IsItemClicked(ImGuiMouseButton_Right)) {

				global_scene->clear_selected_entities();
				global_scene->add_selected_entity(entity);


				if (ImGui::IsItemClicked(ImGuiMouseButton_Right)) {
					ImGui::OpenPopup("ModEnt");
				}
			}

			if (nodeOpen) {
				for (auto child : entity->get_children()) {
					auto childEntity = dynamic_cast<core_entity*>(child);
					if (childEntity && childEntity != entity) {
						renderEntity(childEntity);
					}
				}
				ImGui::TreePop(); 
			}

			
			if (ImGui::BeginPopup("ModEnt")) {
				ImGui::Text("Modify Entity");
				ImGui::Separator();


				char entity_name[256];
				strncpy_s(entity_name, sizeof(entity_name), global_scene->get_crnt_entity()->m_ent_ID.c_str(), _TRUNCATE);



				if (ImGui::InputText("##name", entity_name, IM_ARRAYSIZE(entity_name)))
					global_scene->get_crnt_entity()->m_ent_ID = entity_name;


				if (ImGui::MenuItem("Delete")) {

					global_scene->delete_enity(global_scene->get_crnt_entity());
					global_scene->clear_selected_entities();

					m_renderer->update_draw_data();
				}
				if (ImGui::MenuItem("Duplicate")) {

					auto name = global_scene->get_crnt_entity()->m_ent_ID;

					while (global_scene->does_ent_name_exist(name)) {
						name += "(1)";
					}


					auto crnt = global_scene->get_crnt_entity()->copy_(name);
					global_scene->add_entity(crnt);
					global_scene->clear_selected_entities();
					global_scene->add_selected_entity(crnt);
				}

				// delete this because this is very temporary

				if (ImGui::MenuItem("ADD PARENT")) {
					global_scene->get_selected_entities()[0]->add_parent(global_scene->m_entities[0]);
				}

				ImGui::EndPopup();
			}


			};

		// Render the root entities (only those without parents)
		if (!ents->get_parent()) {
			renderEntity(ents);
		}
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
			for (const auto y : global_scene->m_entities)
			{
				if (_ent_str == y->m_ent_ID)
				{
					does_ent_name_exist = true;
					break;
				}
			}
			if (!does_ent_name_exist)
			{
				global_scene->add_entity(_ent_str);
			}
		}
		
		ImGui::EndPopup();
	}



	ImGui::End();
}
