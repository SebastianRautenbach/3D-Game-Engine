#include "entity sys/components/camera_component.h"
#include "system/camera_3d.h"

wizm::camera_component::camera_component()
{						// fornow
	m_component_type = eCamera;
	m_camera = std::make_shared<camera_core_3d>(1920, 1080);
	m_camera->set_position(get_position());
}

wizm::camera_component::~camera_component()
{
}

void wizm::camera_component::component_preupdate()
{
}

void wizm::camera_component::component_update()
{
	m_camera->set_position(get_world_position());
	auto rot = get_rotation_matrix();
	m_camera->set_rotation_matrix(rot);
}

void wizm::camera_component::component_postupdate()
{
}

std::shared_ptr<core_component> wizm::camera_component::_copy() const
{
	return std::shared_ptr<core_component>();
}


