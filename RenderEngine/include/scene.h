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

		// serialization
		void read_map_data();
		void save_map_data();
		
		
		// entity related
		
		core_entity& add_entity(std::string entity_name);


		// modifying only one entity

		core_entity* get_crnt_entity() {
			return m_selected_entity ? m_selected_entity : nullptr;
		}

		void set_crnt_entity(core_entity* ent) { m_selected_entity = ent; };

	public:
		std::vector<core_entity*> m_entities;

	private:
		core_entity* m_selected_entity;
	};


}
