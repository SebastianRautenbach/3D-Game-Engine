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