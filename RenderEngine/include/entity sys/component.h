#pragma once
#include "component_types.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "system/tag.h"
#include "gl core/core shader.h"

using namespace wizm;

namespace lowlevelsys {


	class core_component {
		
	public:

		virtual void component_preupdate() = 0;
		virtual void component_update() = 0;
		virtual void component_postupdate() = 0;

		// default component shit

		void remove_component();



		// Transform shit

		void set_local_position(glm::vec3 position);
		void set_local_rotation(glm::vec3 rotation);
		void set_local_scale(glm::vec3 scale);

		void add_local_position(glm::vec3 position);
		void add_local_rotation(glm::vec3 rotation);
		void add_local_scale(glm::vec3 scale);


		glm::vec3 get_local_position() { return m_position; }
		glm::vec3 get_local_rotation() { return m_rotation; }
		glm::vec3 get_local_scale() { return m_scale; }


	public:

		eCompType m_component_type;

		bool m_is_active;
		bool m_is_visible;

		wizm::core_tag* component_tags;
		glm::vec3 m_position;
		glm::vec3 m_rotation;
		glm::vec3 m_scale;
	};
}