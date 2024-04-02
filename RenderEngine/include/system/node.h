#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>


namespace wizm {

	class core_node {


	public:

		core_node();


		//----------------------------------------------------------------------------------

		void add_parent(core_node* parent_node) {
			m_parent_node = parent_node;
			m_parent_node->add_child(this);
		}

		void add_child(core_node* child_node) {
			m_child_nodes.emplace_back(child_node);
		}


		//---------------------------------------------------------------------------------- TRANSFORM

		// Setters
		void set_position(const glm::vec3& position);
		void add_position(const glm::vec3& offset); 
		void set_rotation(const glm::vec3& rotation); 
		void add_rotation(const glm::vec3& deltaRotation); 
		void set_scale(const glm::vec3& scale); 
		void add_scale(const glm::vec3& deltaScale); 


		// Getters
		const glm::vec3& get_position() const { return m_translation; }
		const glm::vec3& get_rotation() const { return m_rotation; }
		const glm::vec3& get_scale() const { return m_scale; }
		glm::mat4 get_transform();

	private:
		glm::vec3 m_translation;
		glm::vec3 m_rotation;
		glm::vec3 m_scale;
		glm::mat4 m_transform;

	private:
		core_node* m_parent_node;
		std::vector<core_node*> m_child_nodes;
	};


}