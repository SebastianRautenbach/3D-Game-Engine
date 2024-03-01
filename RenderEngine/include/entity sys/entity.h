#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <vector>
#include "component.h"

namespace wizm {


	class core_entity {
	
		core_entity(std::string ent_ID);
		~core_entity();
	
		
		// entity
		void remame_entity(std::string name);
		void destroy_entity();
		core_entity* get_entity() { return this; }
		


		// component
		
		void add_component(core_component* comp);
		core_component* get_component(eCompType comp_type);
		void remove_component(unsigned int index);
		void set_component(unsigned int index, core_component* comp);
	

	public:

		std::vector<core_component> m_components_list;

		glm::vec3 m_position;
		glm::vec3 m_rotation;
		glm::vec3 m_scale;
	};


}