#include "entity sys/entity.h"


	//////////////////////////////////////////////////////////////////////////
	// DEFAULT CONSTRUCTOR
	//////////////////////////////////////////////////////////////////////////

	//-----------------------------------------------------------------------

wizm::core_entity::core_entity(std::string ent_ID)
	:m_ent_ID(ent_ID)
{

}

	//-----------------------------------------------------------------------

wizm::core_entity::~core_entity()
{
	destroy_entity();
}

void wizm::core_entity::remame_entity(std::string name)
{
	m_ent_ID = name;
}

void wizm::core_entity::destroy_entity()
{
	for (auto& i : m_components_list)
	{
		
	}
}


	//-----------------------------------------------------------------------

void wizm::core_entity::entity_preupdate()
{
	for (auto& i : m_components_list)
	{
		i->component_preupdate();
	}
}

void wizm::core_entity::entity_update()
{
	for (auto& i : m_components_list)
	{
		i->component_update();
	}
}

void wizm::core_entity::entity_postupdate()
{
	for (auto& i : m_components_list)
	{
		i->component_postupdate();
	}
}

//-----------------------------------------------------------------------


void wizm::core_entity::set_position(glm::vec3 position)
{
	

 	for (auto& i : m_components_list)
 	{
 		
 		i->set_local_position(glm::vec3(
 			i->get_local_position().x + position.x - m_position.x,
 			i->get_local_position().y + position.y - m_position.y,
 			i->get_local_position().z + position.z - m_position.z
 		));

		i->center = position;
 	}
 	
	
	m_position = position;

}

void wizm::core_entity::set_rotation(glm::vec3 rotation)
{
	
	
	for (auto& i : m_components_list)
	{


		i->set_world_rotation(glm::vec3(
			i->get_local_rotation().x + rotation.x - m_rotation.x,
			i->get_local_rotation().y + rotation.y - m_rotation.y,
			i->get_local_rotation().z + rotation.z - m_rotation.z
		));

	}

	m_rotation = rotation;

	
}

void wizm::core_entity::set_scale(glm::vec3 scale)
{
	
	
	
	for (auto& i : m_components_list)
	{
		i->set_local_scale(glm::vec3(
			i->get_local_scale().x + scale.x - m_scale.x,
			i->get_local_scale().y + scale.y - m_scale.y,
			i->get_local_scale().z + scale.z - m_scale.z
		));
	}


	m_scale = scale;
	
}

//----------------------------------------------------------------------------
// NEWER SYSTEM

void wizm::core_entity::set_pos(glm::vec3 position)
{
	m_transform = glm::translate(m_transform, position);

}

void wizm::core_entity::set_rot(glm::vec3 rotation)
{
	m_transform = glm::rotate(m_transform, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	m_transform = glm::rotate(m_transform, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	m_transform = glm::rotate(m_transform, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
}

void wizm::core_entity::set_sca(glm::vec3 scale)
{
	m_transform = glm::scale(m_transform, scale);
}

glm::vec3 wizm::core_entity::get_pos()
{
	return glm::vec3(m_transform[3]);
}

glm::quat wizm::core_entity::get_rot()
{
	glm::mat4 rotationMatrix = m_transform;
	rotationMatrix[0] /= get_sca().x;
	rotationMatrix[1] /= get_sca().y;
	rotationMatrix[2] /= get_sca().z;

	glm::quat rotation = glm::quat_cast(rotationMatrix);
	return rotation;
}

glm::vec3 wizm::core_entity::get_sca()
{
	glm::vec3 scaleX = glm::vec3(m_transform[0][0], m_transform[1][0], m_transform[2][0]);
	glm::vec3 scaleY = glm::vec3(m_transform[0][1], m_transform[1][1], m_transform[2][1]);
	glm::vec3 scaleZ = glm::vec3(m_transform[0][2], m_transform[1][2], m_transform[2][2]);

	return glm::vec3(glm::length(scaleX), glm::length(scaleY), glm::length(scaleZ));
}

//-----------------------------------------------------------------------

void wizm::core_entity::add_position(glm::vec3 position)
{
	for (auto& i : m_components_list)
	{
		i->add_local_position(position);
		i->center = m_position + position;
	}

	m_position += position;
}



void wizm::core_entity::add_rotation(glm::vec3 rotation)
{
	for (auto& i : m_components_list)	
	{
		i->set_world_rotation(i->get_local_rotation() + rotation);
	}

	m_rotation += rotation;
}



void wizm::core_entity::add_scale(glm::vec3 scale)
{
	for (auto& i : m_components_list)
	{
		i->add_local_scale(scale);
	}


	m_scale += scale;
}

	//////////////////////////////////////////////////////////////////////////
	// COMPONENTS
	//////////////////////////////////////////////////////////////////////////


	//-----------------------------------------------------------------------

void wizm::core_entity::add_component(std::shared_ptr<core_component> component)
{
	m_components_list.push_back(component);
}


std::shared_ptr<core_component> wizm::core_entity::get_component(eCompType comp_type)
{

	for (auto& i: m_components_list)
	{
		if (i->m_component_type == comp_type)
		{
			return i;
		}
	}


	return nullptr;
}

int wizm::core_entity::get_component_index(eCompType comp_type)
{
	for (int i = 0; i < m_components_list.size(); i++)
	{
		if (m_components_list[i]->m_component_type == comp_type)
			return i;
	}
	return -1;
}


void wizm::core_entity::remove_component(unsigned int index)
{
	m_components_list.erase(m_components_list.begin() + index);
}


void wizm::core_entity::set_component(unsigned int index, std::shared_ptr<core_component> component)
{
	m_components_list[index] = component;
}


	//-----------------------------------------------------------------------