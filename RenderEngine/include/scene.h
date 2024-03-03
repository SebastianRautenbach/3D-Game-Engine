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
		


		
		// entity related
		
		void add_entity(std::string entity_name);

	public:
		std::vector<core_entity*> m_entities;
	};


}
