#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <vector>
#include "component.h"
#include "system/tag.h"
#include <memory>
#include "components/all_components_list.h"

using namespace lowlevelsys;

namespace wizm {


	class core_entity {

	public:
	
		core_entity(std::string ent_ID);
		~core_entity();
	
		
		// entity
		void remame_entity(std::string name);
		void destroy_entity();
		core_entity* get_entity() { return this; }

		void entity_preupdate();
		void entity_update();
		void entity_postupdate();

		void set_position(glm::vec3 position);
		void set_rotation(glm::vec3 rotation);
		void set_scale(glm::vec3 scale);

		void add_position(glm::vec3 position);
		void add_rotation(glm::vec3 rotation);
		void add_scale(glm::vec3 scale);
		


		// component
		
		void add_component(std::shared_ptr<core_component> component);
		std::shared_ptr<core_component> get_component(eCompType comp_type);
		unsigned int get_component_index(eCompType comp_type);
		void remove_component(unsigned int index);
		void set_component(unsigned int index, std::shared_ptr<core_component> component);
	

	public:

		std::string m_ent_ID;

		core_tag* entity_tags;
		std::vector<std::shared_ptr<core_component>> m_components_list;

		glm::vec3 m_position;
		glm::vec3 m_rotation;
		glm::vec3 m_scale;
	};


}