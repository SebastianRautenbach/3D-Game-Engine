#include "system/camera_manager.h"
#include "system/camera_3d.h"

wizm::camera_manager::camera_manager(core_scene* scene)
	:m_scene(scene)
{
}

wizm::camera_manager::~camera_manager()
{
}

bool wizm::camera_manager::update_crnt_camera(bool simulate)
{
	did_change_cam = false;
	if(simulate)
	{
		for (const auto& ent : m_scene->m_entities)
		{
			for (const auto& comp : ent->m_components_list) {

				auto m_cam_comp = std::dynamic_pointer_cast<camera_component>(comp);
				if (m_cam_comp) {

					if (m_cam_comp->is_main_camera) {

						m_crnt_camera = m_cam_comp->m_camera;
						did_change_cam = true;
					}
				}
			}
		}
	}
	else
	{
		m_crnt_camera = m_viewport_camera;
		did_change_cam = true;
	}

	return did_change_cam;
}
