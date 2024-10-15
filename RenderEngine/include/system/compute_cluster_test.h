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
		unsigned int pointLightIndices[50];
		unsigned int spotLightIndices[50];
	};

	struct alignas(16) PointLight
	{
		glm::vec4 position;
		float constant;
		float linear;
		float quadratic;

		glm::vec4 ambient;
		glm::vec4 diffuse;
		glm::vec4 specular;

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
		compute_cluster(std::vector<std::shared_ptr<core_gl_shader>>& shaders, std::shared_ptr<core_gl_shader>& com_shader_cluster, std::shared_ptr<core_gl_shader>& com_shader_cull, std::shared_ptr<camera_core_3d> camera, framebuffer_spec& spec)
			: m_shader_cluster(com_shader_cluster), m_shader_cull(com_shader_cull), m_camera(camera), m_spec(spec), m_shaders(shaders)
		{
			glGenBuffers(1, &clusterGridSSBO);
			glBindBuffer(GL_SHADER_STORAGE_BUFFER, clusterGridSSBO);

			glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(Cluster) * numClusters, nullptr, GL_STATIC_COPY);
			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, clusterGridSSBO);
		}

	public:

		void update_lights() {
			

			if (global_scene->total_component_count() != shader_count || global_scene->m_reloaded) {

				std::vector<std::shared_ptr<pointlight_component>> point_lights;
				std::vector<std::shared_ptr<spotlight_component>> spot_lights;
				std::vector<PointLight> point_lights_list;
				std::vector<SpotLight> spot_lights_list;



				for (auto& i : global_scene->m_entities) {
					for (auto& per_ent : i->m_components_list)
					{
						auto light_comps = std::dynamic_pointer_cast<pointlight_component>(per_ent);
						if (light_comps)
						{
							point_lights.push_back(light_comps);
						//	break;
						}
				
						auto spotlight_comps = std::dynamic_pointer_cast<spotlight_component>(per_ent);
						if (spotlight_comps) {
				
							spot_lights.push_back(spotlight_comps);
						//	break;
						}
					}
				}


				

				for (const auto& light : point_lights) {
					PointLight temp;
					temp.ambient = glm::vec4(light->m_ambient, 1.0);
					temp.position = glm::vec4(light->get_world_position(), 1.0);
					temp.diffuse = glm::vec4(light->m_diffuse, 1.0);
					temp.specular = glm::vec4(light->m_specular, 1.0);
					temp.radius = light->m_radius;
					temp.constant = light->m_constant;
					temp.linear = light->m_linear;
					temp.quadratic = light->m_quadratic;
					point_lights_list.emplace_back(temp);
				}

				for (const auto& light : spot_lights) {

					SpotLight temp;
					temp.ambient = glm::vec4(light->m_ambient, 1.0);
					temp.position = glm::vec4(light->get_world_position(), 1.0);
					temp.diffuse = glm::vec4(light->m_diffuse, 1.0);
					temp.specular = glm::vec4(light->m_specular, 1.0);
					temp.constant = light->m_constant;
					temp.linear = light->m_linear;
					temp.quadratic = light->m_quadratic;

					temp.cutOff = light->m_cutOff;
					temp.outerCutOff = light->m_outerCutOff;
					temp.distance = light->m_distance;

					auto world_rotation = light->get_world_rotation();
					glm::quat rotation_quat = glm::quat(glm::vec3(glm::radians(world_rotation.x), glm::radians(world_rotation.y), glm::radians(world_rotation.z)));
					glm::vec3 rotated_direction = glm::normalize(rotation_quat * glm::vec3(0.0f, -1.0f, 0.0f));
					temp.direction = glm::vec4(rotated_direction, 1.0);

					spot_lights_list.emplace_back(temp);
				}


				//----------------------------------------------------------------------- SPOTLIGHTS

				if(spotLightSSBO)
					glDeleteBuffers(1, &spotLightSSBO);
				
				glGenBuffers(1, &spotLightSSBO);
				glBindBuffer(GL_SHADER_STORAGE_BUFFER, spotLightSSBO);

				glBufferData(GL_SHADER_STORAGE_BUFFER, spot_lights_list.size() * sizeof(SpotLight),
					spot_lights_list.data(), GL_DYNAMIC_DRAW);

				glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, spotLightSSBO);



				//----------------------------------------------------------------------- POINTLIGHTS



				if (pointLightSSBO)
					glDeleteBuffers(1, &pointLightSSBO);

				glGenBuffers(1, &pointLightSSBO);
				glBindBuffer(GL_SHADER_STORAGE_BUFFER, pointLightSSBO);

				glBufferData(GL_SHADER_STORAGE_BUFFER, point_lights_list.size() * sizeof(PointLight),
					point_lights_list.data(), GL_DYNAMIC_DRAW);

				glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, pointLightSSBO);

			
				shader_count = global_scene->total_component_count();
			}
		}

		void update() {

			for (auto shader : m_shaders) {
				if(!shader->is_compute)
				{
					shader->use_shader();
					shader->setFloat("zNear", m_camera->get_near());
					shader->setFloat("zFar", m_camera->get_far());
					shader->setMat4("inverseProjection", glm::inverse(m_camera->get_projection_matrix()));
					shader->setUVec3("gridSize", { gridSizeX, gridSizeY, gridSizeZ });
					shader->setUVec2("screenDimensions", { m_spec.Width, m_spec.Height });
				}
			}

			m_shader_cluster->use_shader();
			m_shader_cluster->setFloat("zNear", m_camera->get_near());
			m_shader_cluster->setFloat("zFar", m_camera->get_far());
			m_shader_cluster->setMat4("inverseProjection", glm::inverse(m_camera->get_projection_matrix()));
			m_shader_cluster->setUVec3("gridSize", { gridSizeX, gridSizeY, gridSizeZ });
			m_shader_cluster->setUVec2("screenDimensions", { m_spec.Width, m_spec.Height });

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

		framebuffer_spec& m_spec;

		unsigned int gridSizeX = 12;
		unsigned int gridSizeY = 12;
		unsigned int gridSizeZ = 24;
		unsigned int numClusters = gridSizeX * gridSizeY * gridSizeZ;


		



	};

}