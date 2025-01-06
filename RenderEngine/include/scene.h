#pragma once
#include "entity sys/entity.h"
#include <vector>


namespace wizm {


	class core_scene {
	public:
		
		// default scene updates
		void scene_preupdate();
		void scene_update(float delta_time, std::shared_ptr<core_gl_shader>& shader);
		void scene_postupdate();
		unsigned int total_component_count();
		bool does_ent_name_exist(std::string name);

		// serialization
		void read_map_data(std::string file_path);
		void save_map_data(std::string path);
		
		
		// entity related 
		std::shared_ptr<core_entity> add_entity(std::shared_ptr<core_entity> entity);
		std::shared_ptr<core_entity> add_entity(std::string entity_name);
		void delete_enity();


		// modifying only one entity
		//-------------------------------------------------------------------------------------------------------- NEW SELECTION
		
		std::vector<std::shared_ptr<core_entity>> get_selected_entities() {
			return m_selected_entities;
		}

		void add_selected_entity(std::shared_ptr<core_entity> ent) {
			for (auto& e : m_selected_entities) {
				if (e == ent) { return; }
			}
			m_selected_entities.emplace_back(ent);
		}

		void remove_selected_entity(std::shared_ptr<core_entity> ent) {
			m_selected_entities.erase(std::find(m_selected_entities.begin(), m_selected_entities.end(), ent));
		}

		void clear_selected_entities() {
			m_selected_entities.clear();
		}


		std::shared_ptr<core_entity> get_crnt_entity() {
			if (m_selected_entities.empty()) { return nullptr; }
			return m_selected_entities[m_selected_entities.size() - 1] ? m_selected_entities[m_selected_entities.size() - 1] : nullptr;
		}

		//-------------------------------------------------------------------------------------------------------- NEW SELECTION


		

		std::shared_ptr<core_entity> get_entity_name(std::string name) {
			for (auto& ent : m_entities) {
				if (ent->m_ent_ID == name)
					return ent;
			}
		}



		// temporarly
		void pre_update_light_components();
		void update_light_components(float delta_time, std::shared_ptr<core_gl_shader>& shader);
		void post_update_light_components();


	private:

		// remove all entities

		void clear_entities();

	public:
		std::vector<std::shared_ptr<core_entity>> m_entities;
		std::vector<std::string> m_destroy_list;
		bool m_reloaded = false;
		std::string current_scene = "";

	private:
		std::vector<std::shared_ptr<core_entity>> m_selected_entities;
		//std::shared_ptr<core_entity> m_selected_entity;
		// might move
		bool m_frustum_loaded = false;
	};


}
