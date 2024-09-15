#pragma once
#include "entity sys/entity.h"
#include <vector>


namespace wizm {


	class core_scene {
	public:
		
		// default scene updates
		void scene_preupdate();
		void scene_update(float delta_time);
		void scene_postupdate();
		unsigned int total_component_count();
		bool does_ent_name_exist(std::string name);

		// serialization
		void read_map_data(std::string file_path);
		void save_map_data(std::string path);
		
		
		// entity related 
		std::shared_ptr<core_entity> add_entity(std::shared_ptr<core_entity> entity);
		std::shared_ptr<core_entity> add_entity(std::string entity_name);


		// modifying only one entity

		std::shared_ptr<core_entity> get_crnt_entity() {
			return m_selected_entity ? m_selected_entity : nullptr;
		}

		std::shared_ptr<core_entity> get_entity_name(std::string name) {
			for (auto& ent : m_entities) {
				if (ent->m_ent_ID == name)
					return ent;
			}
		}

		void set_crnt_entity(std::shared_ptr<core_entity> ent) { 
			m_selected_entity = ent; 
		};


	private:

		// remove all entities

		void clear_entities();

	public:
		std::vector<std::shared_ptr<core_entity>> m_entities;
		bool m_reloaded = false;
		std::string current_scene = "";

	private:
		std::shared_ptr<core_entity> m_selected_entity;
	};


}
