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


	class core_node : public save_node {


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

		core_node* get_parent() { return m_parent_node; }

		std::vector<core_node*> get_children() {
			return m_child_nodes;
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
			if (m_parent_node)
				return glm::vec3(m_parent_node->get_transform() * glm::vec4(m_translation, 1.0f));
			else
				return m_translation;
		}

		glm::mat4 get_rotation_matrix() {

			if (m_parent_node)			// THIS IS WRONG!!!!!!!!!!!!!!!!
				return glm::mat4_cast(glm::quat(m_parent_node->m_rotation));
			else
				return glm::mat4_cast(glm::quat(m_rotation));
		}


		glm::vec3 get_world_rotation() {
			glm::mat3 normal_matrix = glm::mat3(get_transform());
			glm::vec3 euler_angles = glm::eulerAngles(glm::quat_cast(glm::mat4(normal_matrix)));
			return glm::degrees(euler_angles);
		}


		glm::quat get_world_rotation_quat()
		{
			glm::mat3 normal_matrix = glm::mat3(get_transform());
			return glm::quat_cast(glm::mat4(normal_matrix));
		}


		glm::vec3 get_world_scale() {
			if (m_parent_node) {
				return m_parent_node->get_scale() * get_scale();
			}
			else {
				return get_scale();
			}
		}




		void save_data(std::string parent_name, std::string index, filedata::ZER& save_t) const override {}
		void read_saved_data(std::string parent_name, std::string index, filedata::ZER& save_t) override {};


	private:
		glm::vec3 m_translation;
		glm::vec3 m_rotation;
		glm::vec3 m_scale;
		glm::mat4 m_transform;


	private:
		core_node* m_parent_node = nullptr;
		std::vector<core_node*> m_child_nodes;

	public:
		inline glm::vec3 rotate_direction(const glm::vec3& direction, const glm::vec3& axis, float angle_degrees) const {
			float angle_radians = glm::radians(angle_degrees);
			glm::mat4 rotation_matrix = glm::rotate(glm::mat4(1.0f), angle_radians, axis);
			glm::vec4 rotated_direction = rotation_matrix * glm::vec4(direction, 0.0f);
			return glm::vec3(rotated_direction);
		}


	};




}