#include "system/compute_cluster_test.h"
#include "system/camera_3d.h"


wizm::compute_cluster::compute_cluster(std::vector<std::shared_ptr<core_gl_shader>>& shaders, std::shared_ptr<core_gl_shader>& com_shader_cluster, std::shared_ptr<core_gl_shader>& com_shader_cull, std::shared_ptr<camera_manager> camera_manager)
	: m_shader_cluster(com_shader_cluster), m_shader_cull(com_shader_cull), m_camera_manager(camera_manager), m_shaders(shaders)
{
	glGenBuffers(1, &clusterGridSSBO);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, clusterGridSSBO);

	glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(Cluster) * numClusters, nullptr, GL_STATIC_COPY);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, clusterGridSSBO);
}

void wizm::compute_cluster::update_lights()
{
	static std::vector<std::pair<unsigned int, unsigned int>> pointlight_indexes, spotlight_indexes;
	static size_t previous_shader_count = 0;


	if (global_scene->total_component_count() != previous_shader_count || global_scene->m_reloaded) {

		pointlight_indexes.clear();
		spotlight_indexes.clear();

		previous_shader_count = global_scene->total_component_count();

		if (pointLightSSBO || spotLightSSBO) {
			glDeleteBuffers(1, &pointLightSSBO);
			pointLightSSBO = 0;
			glDeleteBuffers(1, &spotLightSSBO);
			spotLightSSBO = 0;
		}

		// Rebuild the list of light indexes (n^2) very slow operatation
		for (unsigned int ent_i = 0; ent_i < global_scene->m_entities.size(); ent_i++) {
			for (unsigned int comp_i = 0; comp_i < global_scene->m_entities[ent_i]->m_components_list.size(); comp_i++) {
				if (global_scene->m_entities[ent_i]->m_components_list[comp_i]->m_component_type == ePointLight) {
					pointlight_indexes.emplace_back(ent_i, comp_i);
				}
				else if (global_scene->m_entities[ent_i]->m_components_list[comp_i]->m_component_type == eSpotLight) {
					spotlight_indexes.emplace_back(ent_i, comp_i);
				}
			}
		}

	}


	std::vector<PointLight> point_lights_list;
	std::vector<SpotLight> spot_lights_list;

	point_lights_list.reserve(pointlight_indexes.size());
	spot_lights_list.reserve(spotlight_indexes.size());

	// Gather point light data
	for (auto& index_pair : pointlight_indexes) {
		
		const auto& [ent_i, comp_i] = index_pair;
		
		auto light_comps = dynamic_cast<pointlight_component*>(
			global_scene->m_entities[ent_i]->m_components_list[comp_i]);

		if (light_comps) {
			PointLight temp;
			temp.position = glm::vec4(light_comps->get_world_position(), 1.0f);
			temp.color = glm::vec4(light_comps->m_diffuse, 1.0f);
			temp.intensity = light_comps->m_intensity;
			temp.radius = light_comps->m_radius;
			point_lights_list.emplace_back(temp);
		}

		

	}

	for (auto& index_pair : spotlight_indexes) {

		const auto& [ent_i, comp_i] = index_pair;
	
		auto spotlight_comp = dynamic_cast<spotlight_component*>(
			global_scene->m_entities[ent_i]->m_components_list[comp_i]);

		if (spotlight_comp) {
			SpotLight temp;
			temp.position = glm::vec4(spotlight_comp->get_world_position(), 1.0f);

			glm::vec3 world_rotation = spotlight_comp->get_world_rotation();
			glm::quat rotation_quat = glm::quat(glm::vec3(glm::radians(world_rotation.x), 
				glm::radians(world_rotation.y), glm::radians(world_rotation.z)));
			glm::vec3 rotated_direction = glm::normalize(rotation_quat * glm::vec3(0.0f, -1.0f, 0.0f));
			
			temp.direction = glm::vec4(rotated_direction, 1.0f);
			temp.cutOff = spotlight_comp->m_cutOff;
			temp.outerCutOff = spotlight_comp->m_outerCutOff;
			temp.distance = spotlight_comp->m_distance;
			temp.constant = spotlight_comp->m_constant;
			temp.quadratic = spotlight_comp->m_quadratic;
			temp.ambient = glm::vec4(spotlight_comp->m_ambient, 1.0f);
			temp.diffuse = glm::vec4(spotlight_comp->m_diffuse, 1.0f);
			temp.specular = glm::vec4(spotlight_comp->m_specular, 1.0f);
			temp.linear = spotlight_comp->m_linear;
			spot_lights_list.emplace_back(temp);
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
			// for some reason using 1 instead of 0 fixes the problem and updates the buffer, this problem is a
			// pain in my -ss to fix, lowkey trying to find a needle in a haystack with a blindfold and a pistol close cuz dammnnn
			glBufferData(GL_SHADER_STORAGE_BUFFER, 1, nullptr, GL_DYNAMIC_DRAW);
		}
		else {
			glBufferData(GL_SHADER_STORAGE_BUFFER, buffer_size, point_lights_list.data(), GL_DYNAMIC_DRAW);
		}
	}
	else {
		glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, buffer_size, point_lights_list.data());
	}

	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, pointLightSSBO);


	//--------------------------------------------------------------------------------------------------------------------------------- SPOTLIGHT

	size_t buffer_sizespt = spot_lights_list.size() * sizeof(SpotLight);
	if (spotLightSSBO == 0) {
		glGenBuffers(1, &spotLightSSBO);
	}
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, spotLightSSBO);
	
	GLint current_buffer_sizespt = 0;

	glGetBufferParameteriv(GL_SHADER_STORAGE_BUFFER, GL_BUFFER_SIZE, &current_buffer_sizespt);


	if (current_buffer_sizespt != static_cast<GLint>(buffer_sizespt) || spot_lights_list.empty()) {
		if (spot_lights_list.empty()) {
			glBufferData(GL_SHADER_STORAGE_BUFFER, 1, nullptr, GL_DYNAMIC_DRAW);
		}
		else {
			glBufferData(GL_SHADER_STORAGE_BUFFER, buffer_sizespt, spot_lights_list.data(), GL_DYNAMIC_DRAW);
		}
	}
	else {
		glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, buffer_sizespt, spot_lights_list.data());
	}

	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, spotLightSSBO);


	//---------------------------------------------------------------------------------------------------------------------------------

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void wizm::compute_cluster::update()
{
	for (auto shader : m_shaders) {
		if (!shader->is_compute)
		{
			glm::mat4 view = glm::mat4(1.0f);
			glm::mat4 projection = glm::mat4(1.0f);

			view = m_camera_manager->m_crnt_camera->get_view_matrix();
			projection = m_camera_manager->m_crnt_camera->get_projection_matrix();

			shader->use_shader();
			shader->setFloat("zNear", m_camera_manager->m_crnt_camera->get_near());
			shader->setFloat("zFar", m_camera_manager->m_crnt_camera->get_far());
			shader->setMat4("inverseProjection", glm::inverse(m_camera_manager->m_crnt_camera->get_projection_matrix()));
			shader->setUVec3("gridSize", { gridSizeX, gridSizeY, gridSizeZ });
			shader->setUVec2("screenDimensions", { m_camera_manager->m_crnt_camera->get_window_size().x, m_camera_manager->m_crnt_camera->get_window_size().y });


			shader->setMat4("view", view);
			shader->setMat4("projection", projection);
			shader->setMat4("perspective", view);
			shader->setVec3("camPos", m_camera_manager->m_crnt_camera->get_position());
			shader->setVec3("camFront", m_camera_manager->m_crnt_camera->get_forward_vector());
		}
	}

	m_shader_cluster->use_shader();
	m_shader_cluster->setFloat("zNear", m_camera_manager->m_crnt_camera->get_near());
	m_shader_cluster->setFloat("zFar", m_camera_manager->m_crnt_camera->get_far());
	m_shader_cluster->setMat4("inverseProjection", glm::inverse(m_camera_manager->m_crnt_camera->get_projection_matrix()));
	m_shader_cluster->setUVec3("gridSize", { gridSizeX, gridSizeY, gridSizeZ });
	m_shader_cluster->setUVec2("screenDimensions", { m_camera_manager->m_crnt_camera->get_window_size().x, m_camera_manager->m_crnt_camera->get_window_size().y });

	glDispatchCompute(gridSizeX, gridSizeY, gridSizeZ);
	glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);


	m_shader_cull->use_shader();
	m_shader_cull->setMat4("viewMatrix", m_camera_manager->m_crnt_camera->get_view_matrix());

	glDispatchCompute(27, 1, 1);
	glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
}
