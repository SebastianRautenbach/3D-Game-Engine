#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



namespace wizm {

	class core_node {


	public:
		void set_pos(glm::vec3 position);
		void set_rot(glm::quat rotation);
		void set_sca(glm::vec3 scale);

		void add_pos(glm::vec3 position);
		void add_rot(glm::vec3 rotation);
		void add_sca(glm::vec3 scale);


		glm::vec3 get_pos();
		glm::quat get_rot();
		glm::vec3 get_sca();

	public:
		glm::mat4 m_transform;

	private:
		core_node* m_parent_node;
	};


}