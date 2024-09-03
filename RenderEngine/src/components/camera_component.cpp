#include "entity sys/components/camera_component.h"
#include "system/3d_core_camera.h"

wizm::camera_component::camera_component()
{
}

wizm::camera_component::~camera_component()
{
}

void wizm::camera_component::component_preupdate()
{
}

void wizm::camera_component::component_update()
{
}

void wizm::camera_component::component_postupdate()
{
}

std::shared_ptr<core_component> wizm::camera_component::_copy() const
{
	return std::shared_ptr<core_component>();
}
