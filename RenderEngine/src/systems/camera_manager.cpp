#include "system/camera_manager.h"

wizm::camera_manager::camera_manager(core_scene* scene)
	:m_scene(scene)
{
}

wizm::camera_manager::~camera_manager()
{
}

void wizm::camera_manager::update_crnt_camera(bool simulate)
{
	if(simulate)
	{
		for (const auto& ent : m_scene->m_entities)
		{
			for (const auto& comp : ent->m_components_list) {

				auto m_cam_comp = std::dynamic_pointer_cast<camera_component>(comp);
				if (m_cam_comp) {

					if (m_cam_comp->is_main_camera) {

						m_crnt_camera = m_cam_comp->m_camera;
					}
				}
			}
		}
	}
	else
	{
		m_crnt_camera = m_viewport_camera;
	}
}
