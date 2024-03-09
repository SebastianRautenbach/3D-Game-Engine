#include "entity sys/component.h"
#include <iostream>

void lowlevelsys::core_component::remove_component()
{
}

//------------------------------------------------------------------------------- 

void lowlevelsys::core_component::add_local_position(glm::vec3 posistion)
{
	m_model_mtx = glm::translate(m_model_mtx, glm::vec3(m_position + posistion));
	m_position += posistion;
}


void lowlevelsys::core_component::add_local_rotation(glm::vec3 rotation)
{
	m_model_mtx = glm::rotate(m_model_mtx, rotation.x + m_rotation.x, glm::vec3(1, 0, 0));
	m_model_mtx = glm::rotate(m_model_mtx, rotation.y + m_rotation.y, glm::vec3(0, 1, 0));
	m_model_mtx = glm::rotate(m_model_mtx, rotation.z + m_rotation.z, glm::vec3(0, 0, 1));
	m_rotation += rotation;
}


void lowlevelsys::core_component::add_local_scale(glm::vec3 scale)
{
	m_model_mtx = glm::scale(m_model_mtx, m_scale + scale);
	m_scale += scale;
}


//------------------------------------------------------------------------------- 


void lowlevelsys::core_component::set_local_rotation(glm::vec3 rotation)
{
	m_model_mtx = glm::rotate(m_model_mtx, rotation.x, glm::vec3(1, 0, 0));
	m_model_mtx = glm::rotate(m_model_mtx, rotation.y, glm::vec3(0, 1, 0));
	m_model_mtx = glm::rotate(m_model_mtx, rotation.z, glm::vec3(0, 0, 1));
	m_rotation = rotation;
}

void lowlevelsys::core_component::set_local_position(glm::vec3 position)
{
	m_model_mtx = glm::translate(m_model_mtx, position);
	m_position = position;
}

void lowlevelsys::core_component::set_local_scale(glm::vec3 scale)
{
	m_model_mtx = glm::scale(m_model_mtx, scale);
	m_scale = scale;
}
