#pragma once
#include "component_types.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
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

		void set_model_mtx(glm::mat4& model);

		void add_local_position(glm::vec3 posistion);
		void add_local_rotation(glm::vec3 rotation);
		void add_local_scale(glm::vec3 scale);

		void set_local_rotation(glm::vec3 rotation);
		void set_local_position(glm::vec3 position);
		void set_local_scale(glm::vec3 scale);

		// temp single_rotation

		void add_world_rotation( float angle);


		// rather then changing the way the whole engine works lets
		// just change the var to a matrix and the function change it
		// acordingly 

		glm::vec3 get_local_position() { return m_position; }
		glm::vec3 get_local_rotation() { return m_rotation; }
		glm::vec3 get_local_scale() { return m_scale; }
		glm::mat4 get_model_mtx() { return m_model_mtx; }

	public:

		//-------------------------

		glm::mat4 m_model_mtx;

		//------------------------- 

		eCompType m_component_type;

		bool m_is_active;
		bool m_is_visible;

		wizm::core_tag* component_tags;

		glm::vec3 center;
		glm::vec3 m_position;
		glm::vec3 m_rotation;
		glm::vec3 m_scale;
	};
}