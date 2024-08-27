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
			if (std::dynamic_pointer_cast<pointlight_component>(comp)) {
				m_billboard_core->draw(comp->get_transform(), eLight);
			}
			else if (std::dynamic_pointer_cast<directionallight_component>(comp))
			{
				m_billboard_core->draw(comp->get_transform(), eDirLight);

			}
		}
	}
}
