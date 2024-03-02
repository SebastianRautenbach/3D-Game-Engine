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

void wizm::core_entity::set_position(glm::vec3 position)
{
	m_position = position;

	for (auto& i : m_components_list)
	{
		
		i->set_local_position(glm::vec3(
			i->get_local_position().x + m_position.x,
			i->get_local_position().y + m_position.y,
			i->get_local_position().z + m_position.z
		));
	}
}

void wizm::core_entity::set_rotation(glm::vec3 rotation)
{
	m_rotation = rotation;
	
	for (auto& i : m_components_list)
	{
		i->set_local_rotation(glm::vec3(
			i->get_local_rotation().x + m_rotation.x,
			i->get_local_rotation().y + m_rotation.y,
			i->get_local_rotation().z + m_rotation.z
		));

	}



	
}

void wizm::core_entity::set_scale(glm::vec3 scale)
{
	
	m_scale = scale;
	
	for (auto& i : m_components_list)
	{
		i->set_local_scale(glm::vec3(
			i->get_local_scale().x + m_scale.x,
			i->get_local_scale().y + m_scale.y,
			i->get_local_scale().z + m_scale.z
		));
	}



	
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

unsigned int wizm::core_entity::get_component_index(eCompType comp_type)
{
	for (int i = 0; i < m_components_list.size(); i++)
	{
		if (m_components_list[i]->m_component_type == comp_type)
			return i;
	}
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