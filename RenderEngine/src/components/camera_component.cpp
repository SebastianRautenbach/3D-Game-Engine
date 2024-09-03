#include "entity sys/components/camera_component.h"
#include "system/3d_core_camera.h"

wizm::camera_component::camera_component()
{						// fornow
	m_component_type = eCamera;
	m_camera = std::make_shared<core_3d_camera>(1920, 1080);
	m_camera->SetPosition(get_position());
}

wizm::camera_component::~camera_component()
{
}

void wizm::camera_component::component_preupdate()
{
}

void wizm::camera_component::component_update()
{
	m_camera->SetPosition(get_world_position());
	m_camera->SetRotation(get_world_rotation_quat());
}

void wizm::camera_component::component_postupdate()
{
}

std::shared_ptr<core_component> wizm::camera_component::_copy() const
{
	return std::shared_ptr<core_component>();
}
