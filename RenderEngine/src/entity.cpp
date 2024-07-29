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
	delete entity_tags;
	m_components_list.clear();
	entity_tags = nullptr;
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
// COPY
//////////////////////////////////////////////////////////////////////////


//-----------------------------------------------------------------------

std::shared_ptr<core_entity> wizm::core_entity::copy_() const
{
	std::string new_ent_ID = m_ent_ID + "(1)";
	std::shared_ptr<core_entity> new_entity = std::make_shared<core_entity>(new_ent_ID);
	
	new_entity->set_position(get_position());
	new_entity->set_rotation(get_rotation());
	new_entity->set_scale(get_scale());

	if (entity_tags) {
		new_entity->entity_tags->tags = this->entity_tags->tags;
	}


	for (const auto& component : m_components_list)
	{
		auto pc_comp = std::dynamic_pointer_cast<pointlight_component>(component);
		if (pc_comp) {
			auto new_pc_comp = std::make_shared<pointlight_component>();
			
			new_pc_comp->set_position(pc_comp->get_position());
			new_pc_comp->set_rotation(pc_comp->get_rotation());
			new_pc_comp->set_scale(pc_comp->get_scale());

			new_pc_comp->light_index = pc_comp->light_index + 1;
			new_pc_comp->m_ambient = pc_comp->m_ambient;
			new_pc_comp->m_constant = pc_comp->m_constant;
			new_pc_comp->m_diffuse = pc_comp->m_diffuse;
			new_pc_comp->m_is_active = pc_comp->m_is_active;
			new_pc_comp->m_is_visible = pc_comp->m_is_visible;
			new_pc_comp->m_linear = pc_comp->m_linear;
			new_pc_comp->m_quadratic = pc_comp->m_quadratic;
			new_pc_comp->m_radius = pc_comp->m_radius;
			new_pc_comp->m_specular = pc_comp->m_specular;
			new_pc_comp->shader = pc_comp->shader;


			new_entity->add_component(new_pc_comp);
			break;
		}
		auto sc_comp = std::dynamic_pointer_cast<staticmesh_component>(component);
		if (sc_comp) {
			auto new_sc_comp = std::make_shared<staticmesh_component>();


			new_sc_comp->set_position(sc_comp->get_position());
			new_sc_comp->set_rotation(sc_comp->get_rotation());
			new_sc_comp->set_scale(sc_comp->get_scale());


			new_sc_comp->m_asset_id = sc_comp->m_asset_id;
			new_sc_comp->m_is_active = sc_comp->m_is_active;
			*new_sc_comp->m_material = *sc_comp->m_material;

			new_sc_comp->m_model = sc_comp->m_model;

			new_entity->add_component(new_sc_comp);

			break;
		}
		auto dl_comp = std::dynamic_pointer_cast<directionallight_component>(component);
		if (dl_comp) {
			std::cout << "dupe directionallight_component\n";
			break;
		}
		
		//std::shared_ptr<core_component> cloned_component = component->copy_();
		//new_entity->add_component(cloned_component);
	}


	return new_entity;
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

void wizm::core_entity::read_saved_data(std::string parent_name, std::string index, filedata::ZER& save_t)
{
	set_position(glm::vec3(
		save_t[m_ent_ID]["transform"].get_float("position")[0],
		save_t[m_ent_ID]["transform"].get_float("position")[1],
		save_t[m_ent_ID]["transform"].get_float("position")[2]));

	set_rotation(glm::vec3(
		save_t[m_ent_ID]["transform"].get_float("rotation")[0],
		save_t[m_ent_ID]["transform"].get_float("rotation")[1],
		save_t[m_ent_ID]["transform"].get_float("rotation")[2]));

	set_scale(glm::vec3(
		save_t[m_ent_ID]["transform"].get_float("scale")[0],
		save_t[m_ent_ID]["transform"].get_float("scale")[1],
		save_t[m_ent_ID]["transform"].get_float("scale")[2]));



	//-------------------------------------------------------------------------------- COMPONENTS
	for (auto& i : save_t[m_ent_ID].class_properties) {

		//--- POINT LIGHT

		if (i.first.find("pointlight") != -1) {
			auto c = add_component(std::make_shared<pointlight_component>());
			c->read_saved_data(m_ent_ID, i.first, save_t);
		}

		//--- DIRECTIONAL LIGHT

		if (i.first.find("directionallight") != -1) {
			auto c = add_component(std::make_shared<directionallight_component>());
			c->read_saved_data(m_ent_ID, i.first, save_t);
		}

		//--- MESH COMPONENT

		if (i.first.find("staticmesh") != -1) {
			auto c = add_component(std::make_shared<staticmesh_component>());
			c->read_saved_data(m_ent_ID, i.first, save_t);
		}

	}
}

void wizm::core_entity::save_data(std::string parent_name, std::string index, filedata::ZER& save_t) const
{

	save_t[m_ent_ID]["transform"].set_float("position", { get_position().x, get_position().y, get_position().z });
	save_t[m_ent_ID]["transform"].set_float("rotation", { get_rotation().x, get_rotation().y, get_rotation().z });
	save_t[m_ent_ID]["transform"].set_float("scale", { get_scale().x, get_scale().y, get_scale().z });



	save_t[m_ent_ID]["tags"].set_string("tags", entity_tags->tags);

	for (int i = 0; i < m_components_list.size(); i++) {
		m_components_list[i]->save_data(m_ent_ID, std::to_string(i), save_t);
	}
}


	//-----------------------------------------------------------------------