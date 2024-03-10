#include "entity sys/component.h"
#include <iostream>

void lowlevelsys::core_component::remove_component()
{
}

//------------------------------------------------------------------------------- 

void lowlevelsys::core_component::set_model_mtx(glm::mat4& model)
{
	m_model_mtx = model;
}

//------------------------------------------------------------------------------- 


void lowlevelsys::core_component::add_local_position(glm::vec3 posistion)
{
	m_model_mtx = glm::translate(m_model_mtx , glm::vec3(m_position + posistion));
	m_position += posistion;
}


void lowlevelsys::core_component::add_local_rotation(glm::vec3 rotation)
{
	m_rotation += rotation;
	m_model_mtx = glm::rotate(m_model_mtx , m_rotation.x, glm::vec3(1, 0, 0));
	m_model_mtx = glm::rotate(m_model_mtx , m_rotation.y, glm::vec3(0, 1, 0));
	m_model_mtx = glm::rotate(m_model_mtx , m_rotation.z, glm::vec3(0, 0, 1));
}


void lowlevelsys::core_component::add_local_scale(glm::vec3 scale)
{
	m_model_mtx = glm::scale(m_model_mtx , m_scale + scale);
	m_scale += scale;
}


//------------------------------------------------------------------------------- 


void lowlevelsys::core_component::set_local_rotation(glm::vec3 rotation)
{
	m_rotation = rotation;
	m_model_mtx = glm::rotate(m_model_mtx , m_rotation.x, glm::vec3(1, 0, 0));
	m_model_mtx = glm::rotate(m_model_mtx , m_rotation.y, glm::vec3(0, 1, 0));
	m_model_mtx = glm::rotate(m_model_mtx , m_rotation.z, glm::vec3(0, 0, 1));
}

void lowlevelsys::core_component::set_local_position(glm::vec3 position)
{
	m_position = position;
	m_model_mtx = glm::translate(m_model_mtx , m_position);
}

void lowlevelsys::core_component::set_local_scale(glm::vec3 scale)
{
	m_model_mtx = glm::scale(m_model_mtx , scale);
	m_scale = scale;
}


//------------------------------------------------------------------------------- 



void lowlevelsys::core_component::set_world_rotation(glm::vec3 rotation)
{
	m_rotation = rotation;
	glm::mat4 m4rotation = glm::mat4(1);
	m4rotation = glm::rotate(glm::mat4(1.0f), m_rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	m4rotation = glm::rotate(glm::mat4(1.0f), m_rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	m4rotation = glm::rotate(glm::mat4(1.0f), m_rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	m_model_mtx = glm::translate(glm::mat4(1.0f), center) * m4rotation * glm::translate(glm::mat4(1.0f), -center) * m_model_mtx;
}
