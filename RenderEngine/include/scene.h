#pragma once
#include "entity sys/entity.h"
#include <vector>


namespace wizm {


	class core_scene {
	public:
		
		// default scene updates
		void scene_preupdate();
		void scene_update();
		void scene_postupdate();
		unsigned int total_component_count();

		// serialization
		void read_map_data(std::string file_path);
		void save_map_data(std::string path);
		
		
		// entity related
		
		core_entity& add_entity(std::string entity_name);


		// modifying only one entity

		core_entity* get_crnt_entity() {
			return m_selected_entity ? m_selected_entity : nullptr;
		}

		void set_crnt_entity(core_entity* ent) { m_selected_entity = ent; };


	private:

		// remove all entities

		void clear_entities();

	public:
		std::vector<core_entity*> m_entities;
		bool m_reloaded = false;
		std::string current_scene = "";

	private:
		core_entity* m_selected_entity;
	};


}
