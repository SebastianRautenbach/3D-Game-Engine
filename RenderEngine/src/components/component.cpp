#include "entity sys/component.h"
#include <iostream>

void lowlevelsys::core_component::remove_component()
{
}

void lowlevelsys::core_component::set_local_position(glm::vec3 position)
{
	m_position = position;
}

void lowlevelsys::core_component::set_local_rotation(glm::vec3 rotation)
{
	m_rotation = rotation;
}

void lowlevelsys::core_component::set_local_scale(glm::vec3 scale)
{
	m_scale = scale;
}

void lowlevelsys::core_component::add_local_position(glm::vec3 position)
{
}

void lowlevelsys::core_component::add_local_rotation(glm::vec3 rotation)
{
}

void lowlevelsys::core_component::add_local_scale(glm::vec3 scale)
{
}
