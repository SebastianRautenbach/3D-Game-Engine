#include "entity sys/entity.h"


	//////////////////////////////////////////////////////////////////////////
	// DEFAULT CONSTRUCTOR
	//////////////////////////////////////////////////////////////////////////

	//-----------------------------------------------------------------------

wizm::core_entity::core_entity(std::string ent_ID)
	:m_ent_ID(ent_ID)
{
	entity_tags = new core_tag();
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
	delete entity_tags;
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


	//////////////////////////////////////////////////////////////////////////
	// COMPONENTS
	//////////////////////////////////////////////////////////////////////////


	//-----------------------------------------------------------------------

std::shared_ptr<core_component> wizm::core_entity::add_component(std::shared_ptr<core_component> component)
{
	component->add_parent(this);
	m_components_list.push_back(component);
	return component;
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

void wizm::core_entity::read_saved_data(std::string parent_name, std::string index)
{
	filedata::ZER save_;
	save_.read_file_cntx();

	set_position(glm::vec3(
		save_[m_ent_ID]["transform"].get_float("position")[0],
		save_[m_ent_ID]["transform"].get_float("position")[1],
		save_[m_ent_ID]["transform"].get_float("position")[2]));

	set_rotation(glm::vec3(
		save_[m_ent_ID]["transform"].get_float("rotation")[0],
		save_[m_ent_ID]["transform"].get_float("rotation")[1],
		save_[m_ent_ID]["transform"].get_float("rotation")[2]));

	set_scale(glm::vec3(
		save_[m_ent_ID]["transform"].get_float("scale")[0],
		save_[m_ent_ID]["transform"].get_float("scale")[1],
		save_[m_ent_ID]["transform"].get_float("scale")[2]));



	//-------------------------------------------------------------------------------- COMPONENTS
	for (auto& i : save_[m_ent_ID].class_properties) {

		//--- POINT LIGHT

		if (i.first.find("pointlight") != -1) {
			auto c = add_component(std::make_shared<pointlight_component>());
			c->read_saved_data(m_ent_ID, i.first);
		}

		//--- DIRECTIONAL LIGHT

		if (i.first.find("directionallight") != -1) {
			auto c = add_component(std::make_shared<directionallight_component>());
			c->read_saved_data(m_ent_ID, i.first);
		}

		//--- MESH COMPONENT

		if (i.first.find("staticmesh") != -1) {
			auto c = add_component(std::make_shared<staticmesh_component>(""));
			c->read_saved_data(m_ent_ID, i.first);
		}

	}
}

void wizm::core_entity::save_data(std::string parent_name, std::string index) const
{
	filedata::ZER save_;
	save_.read_file_cntx();

	save_[m_ent_ID]["transform"].set_float("position", { get_position().x, get_position().y, get_position().z });
	save_[m_ent_ID]["transform"].set_float("rotation", { get_rotation().x, get_rotation().y, get_rotation().z });
	save_[m_ent_ID]["transform"].set_float("scale", { get_scale().x, get_scale().y, get_scale().z });



	save_[m_ent_ID]["tags"].set_string("tags", entity_tags->tags);
	save_.save_file(save_);

	for (int i = 0; i < m_components_list.size(); i++) {
		m_components_list[i]->save_data(m_ent_ID, std::to_string(i));
	}
}


	//-----------------------------------------------------------------------