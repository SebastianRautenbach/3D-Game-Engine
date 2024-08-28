#include "system/billboard_manager.h"

wizm::billboard_manager::billboard_manager(core_scene* scene, std::shared_ptr<core_gl_shader> shader)
	:m_scene(scene), m_shader(shader)
{
	m_billboard_core = new billboard_core(m_shader);
}

void wizm::billboard_manager::render()
{
	for (const auto& ent : m_scene->m_entities) {
		for (const auto& comp : ent->m_components_list) {

			m_shader->setVec3("tint", glm::vec3(1.0f));
			
			auto point_light = std::dynamic_pointer_cast<pointlight_component>(comp);
			auto directional_light = std::dynamic_pointer_cast<directionallight_component>(comp);
			auto spot_light = std::dynamic_pointer_cast<spotlight_component>(comp);
			
			if (point_light) {
			//	std::cout << ent->m_ent_ID << ":" << point_light->m_diffuse.x << "," << point_light->m_diffuse.y << "," << point_light->m_diffuse.z << std::endl;
				m_billboard_core->draw(comp->get_transform(), eLightB, point_light->m_diffuse);
			}
			else if (directional_light)
			{
				m_billboard_core->draw(comp->get_transform(), eDirLightB, directional_light->m_ambient);
			}
			else if (spot_light)
			{
				m_billboard_core->draw(comp->get_transform(), eSpotLightB, spot_light->m_diffuse);
			}
		}
	}
}
