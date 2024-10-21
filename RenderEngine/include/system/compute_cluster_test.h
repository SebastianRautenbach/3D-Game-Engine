#pragma once
#include "gl core/core shader.h"
#include "system/camera_3d.h"
#include <memory>
#include "gl core/vertex_buffer.h"
#include "entity sys/components/all_components_list.h"
#include "system/scene_manager.h"

namespace wizm {


	struct alignas(16) Cluster
	{
		glm::vec4 minPoint;
		glm::vec4 maxPoint;
		unsigned int count;
		unsigned int pointLightIndices[100];
		unsigned int spotLightIndices[100];
	};




	struct alignas(16) PointLight
	{
		glm::vec4 position;
		float constant;
		float linear;
		float quadratic;
		float padding1;

		glm::vec4 ambient;
		glm::vec4 diffuse;
		glm::vec4 specular;

		float radius;
		float padding2[3];
	};


	struct alignas(16) PointLightPre {

		glm::vec4 position;
		glm::vec4 color;
		float intensity;
		float radius;

	};


	struct alignas(16) SpotLight
	{
		glm::vec4 position;
		glm::vec4 direction;
		float cutOff;
		float outerCutOff;
		float distance;

		float constant;
		float linear;
		float quadratic;

		glm::vec4 ambient;
		glm::vec4 diffuse;
		glm::vec4 specular;
	};



	class compute_cluster {
	public:
		compute_cluster(std::vector<std::shared_ptr<core_gl_shader>>& shaders, std::shared_ptr<core_gl_shader>& com_shader_cluster, std::shared_ptr<core_gl_shader>& com_shader_cull, std::shared_ptr<camera_core_3d> camera)
			: m_shader_cluster(com_shader_cluster), m_shader_cull(com_shader_cull), m_camera(camera), m_shaders(shaders)
		{
			glGenBuffers(1, &clusterGridSSBO);
			glBindBuffer(GL_SHADER_STORAGE_BUFFER, clusterGridSSBO);

			glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(Cluster) * numClusters, nullptr, GL_STATIC_COPY);
			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, clusterGridSSBO);
		}

	public:

		void update_lights() { 
		
			static std::vector<std::pair<unsigned int, unsigned int>> light_indexes;
			static size_t previous_shader_count = 0;
			static GLuint pointLightSSBO = 0;


			if (global_scene->total_component_count() != previous_shader_count || global_scene->m_reloaded) {
				
				light_indexes.clear();
				previous_shader_count = global_scene->total_component_count();

				if (pointLightSSBO) {
					glDeleteBuffers(1, &pointLightSSBO);
					pointLightSSBO = 0;
				}

				// Rebuild the list of light indexes
				for (unsigned int ent_i = 0; ent_i < global_scene->m_entities.size(); ent_i++) {
					for (unsigned int comp_i = 0; comp_i < global_scene->m_entities[ent_i]->m_components_list.size(); comp_i++) {
						if (is_light_component(global_scene->m_entities[ent_i]->m_components_list[comp_i]->m_component_type)) {
							light_indexes.emplace_back(ent_i, comp_i);
						}
					}
				}

			}

			
			std::vector<PointLight> point_lights_list;
			point_lights_list.reserve(light_indexes.size());

			// Gather point light data
			for (auto& index_pair : light_indexes) {
				const auto& [ent_i, comp_i] = index_pair;
				auto light_comps = std::dynamic_pointer_cast<pointlight_component>(
					global_scene->m_entities[ent_i]->m_components_list[comp_i]);

				if (light_comps) {
					PointLight temp;
					temp.position = glm::vec4(light_comps->get_world_position(), 1.0f);
					temp.constant = light_comps->m_constant;
					temp.linear = light_comps->m_linear;
					temp.quadratic = light_comps->m_quadratic;
					temp.ambient = glm::vec4(light_comps->m_ambient, 1.0f);
					temp.diffuse = glm::vec4(light_comps->m_diffuse, 1.0f);
					temp.specular = glm::vec4(light_comps->m_specular, 1.0f);
					temp.radius = light_comps->m_radius;

					point_lights_list.emplace_back(temp);
				}
			}

	
			size_t buffer_size = point_lights_list.size() * sizeof(PointLight);
			if (pointLightSSBO == 0) {
				glGenBuffers(1, &pointLightSSBO);
			}

			glBindBuffer(GL_SHADER_STORAGE_BUFFER, pointLightSSBO);

	
			GLint current_buffer_size = 0;
			glGetBufferParameteriv(GL_SHADER_STORAGE_BUFFER, GL_BUFFER_SIZE, &current_buffer_size);

			if (current_buffer_size != static_cast<GLint>(buffer_size) || point_lights_list.empty()) {
				if (point_lights_list.empty()) {
					glBufferData(GL_SHADER_STORAGE_BUFFER, 0, nullptr, GL_DYNAMIC_DRAW);
				}
				else {
					glBufferData(GL_SHADER_STORAGE_BUFFER, buffer_size, point_lights_list.data(), GL_DYNAMIC_DRAW);
				}
			}
			else {				
				glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, buffer_size, point_lights_list.data());
			}


	
			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, pointLightSSBO);

	
			glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

		}

		void update() {

			for (auto shader : m_shaders) {
				if (!shader->is_compute)
				{
					glm::mat4 view = glm::mat4(1.0f);
					glm::mat4 projection = glm::mat4(1.0f);
					
					view = m_camera->get_view_matrix();
					projection = m_camera->get_projection_matrix();

					shader->use_shader();
					shader->setFloat("zNear", m_camera->get_near());
					shader->setFloat("zFar", m_camera->get_far());
					shader->setMat4("inverseProjection", glm::inverse(m_camera->get_projection_matrix()));
					shader->setUVec3("gridSize", { gridSizeX, gridSizeY, gridSizeZ });
					shader->setUVec2("screenDimensions", { m_camera->get_window_size().x, m_camera->get_window_size().y });

							
					shader->setMat4("view", view);
					shader->setMat4("projection", projection);
					shader->setMat4("perspective", view);
					shader->setVec3("camPos", m_camera->get_position());
					shader->setVec3("camFront", m_camera->get_forward_vector());
				}
			}

			m_shader_cluster->use_shader();
			m_shader_cluster->setFloat("zNear", m_camera->get_near());
			m_shader_cluster->setFloat("zFar", m_camera->get_far());
			m_shader_cluster->setMat4("inverseProjection", glm::inverse(m_camera->get_projection_matrix()));
			m_shader_cluster->setUVec3("gridSize", { gridSizeX, gridSizeY, gridSizeZ });
			m_shader_cluster->setUVec2("screenDimensions", { m_camera->get_window_size().x, m_camera->get_window_size().y });

			glDispatchCompute(gridSizeX, gridSizeY, gridSizeZ);
			glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);


			m_shader_cull->use_shader();
			m_shader_cull->setMat4("viewMatrix", m_camera->get_view_matrix());

			glDispatchCompute(27, 1, 1);
			glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

		}

	private:
		std::vector<std::shared_ptr<core_gl_shader>>& m_shaders;
		
		std::shared_ptr<core_gl_shader> m_shader_cull;
		std::shared_ptr<core_gl_shader> m_shader_cluster;


		std::shared_ptr<camera_core_3d> m_camera;
		unsigned int clusterGridSSBO, pointLightSSBO, spotLightSSBO, shader_count = 0;


		
		unsigned int gridSizeX = 12;
		unsigned int gridSizeY = 12;
		unsigned int gridSizeZ = 24;
		unsigned int numClusters = gridSizeX * gridSizeY * gridSizeZ;


		



	};

}