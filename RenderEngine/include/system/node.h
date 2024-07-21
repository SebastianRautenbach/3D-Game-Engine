#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "other utils/ZER.h"


namespace wizm {

	class save_node {
		
		virtual void save_data(std::string parent_name, std::string index, filedata::ZER& save_t) const = 0;
		virtual void read_saved_data(std::string parent_name, std::string index, filedata::ZER& save_t) = 0;
	};
	

	class core_node : public save_node{


	public:

		core_node();
		~core_node();


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
		const glm::vec3& get_position() const { return m_translation; }		   // <<  These are local transforms
		const glm::vec3& get_rotation() const { return m_rotation; }		   // <<  These are local transforms
		const glm::vec3& get_scale() const { return m_scale; }				   // <<  These are local transforms

		glm::mat4 get_transform();

		glm::vec3 get_world_position() {
			glm::mat4 worldTransform = get_transform();
			return glm::vec3(worldTransform[3]);
		}
		glm::vec3 get_world_rotation() {
			if (m_parent_node)
				return m_parent_node->get_rotation();
			else
				return glm::vec3(0.0);
		}

		void save_data(std::string parent_name, std::string index, filedata::ZER& save_t) const override {}
		void read_saved_data(std::string parent_name, std::string index, filedata::ZER& save_t) override {};
		

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