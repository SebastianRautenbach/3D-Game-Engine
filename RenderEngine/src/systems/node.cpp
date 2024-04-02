#include "system/node.h"


//----------------------------------------------------------------------------------------------



void wizm::core_node::set_pos(glm::vec3 position)
{
	m_transform = glm::translate(m_transform, position);
}

void wizm::core_node::set_rot(glm::quat rotation)
{
	m_transform = glm::mat4_cast(rotation);
}

void wizm::core_node::set_sca(glm::vec3 scale)
{
	m_transform = glm::scale(m_transform, scale);
}


//----------------------------------------------------------------------------------------------


void wizm::core_node::add_pos(glm::vec3 position)
{
	position += get_pos();
	m_transform = glm::translate(m_transform, position);
}

void wizm::core_node::add_rot(glm::vec3 rotation)
{
	glm::quat x_quat = glm::angleAxis(rotation.x, glm::vec3(1, 0, 0));
	glm::quat y_quat = glm::angleAxis(rotation.y, glm::vec3(0, 1, 0));
	glm::quat z_quat = glm::angleAxis(rotation.z, glm::vec3(0, 0, 1));

	glm::quat combined_quat = z_quat * y_quat * x_quat;
	glm::quat new_rot = combined_quat * get_rot();
	
	
	set_rot(new_rot);
}

void wizm::core_node::add_sca(glm::vec3 scale)
{
	scale += get_sca();
	m_transform = glm::scale(m_transform, scale);
}



//----------------------------------------------------------------------------------------------


glm::vec3 wizm::core_node::get_pos()
{
	return glm::vec3(m_transform[3]);
}

glm::quat wizm::core_node::get_rot()
{
	glm::mat4 rotationMatrix = m_transform;
	rotationMatrix[0] /= get_sca().x;
	rotationMatrix[1] /= get_sca().y;
	rotationMatrix[2] /= get_sca().z;

	glm::quat rotation = glm::quat_cast(rotationMatrix);
	return rotation;
}

glm::vec3 wizm::core_node::get_sca()
{
	glm::vec3 scaleX = glm::vec3(m_transform[0][0], m_transform[1][0], m_transform[2][0]);
	glm::vec3 scaleY = glm::vec3(m_transform[0][1], m_transform[1][1], m_transform[2][1]);
	glm::vec3 scaleZ = glm::vec3(m_transform[0][2], m_transform[1][2], m_transform[2][2]);

	return glm::vec3(glm::length(scaleX), glm::length(scaleY), glm::length(scaleZ));
}
