#include "system/billboard_manager.h"
#include "other utils/common.h"
#include "system/scene_manager.h"

wizm::billboard_manager::billboard_manager(std::shared_ptr<core_gl_shader> shader)
	: m_shader(shader)
{
	m_billboard_core = new billboard_core(m_shader);
}

void wizm::billboard_manager::render()
{
	if(engine_status == EDITOR_STATUS)
	{
		for (const auto& ent : global_scene->m_entities) {
			for (const auto& comp : ent->m_components_list) {

				m_shader->setVec3("tint", glm::vec3(1.0f));

				if (comp->m_component_type == ePointLight) {
					m_billboard_core->draw(comp->get_transform(), eLightB);
				}
				else if (comp->m_component_type == eDirectionalLight)
				{
					m_billboard_core->draw(comp->get_transform(), eDirLightB);
				}
				else if (comp->m_component_type == eSpotLight)
				{
					m_billboard_core->draw(comp->get_transform(), eSpotLightB);
				}
				else if (comp->m_component_type == eCamera)
				{
					m_billboard_core->draw(comp->get_transform(), eCameraB);
				}
			}
		}
	}
}
