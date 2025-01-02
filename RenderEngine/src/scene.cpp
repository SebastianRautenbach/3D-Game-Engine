#include "scene.h"


namespace wizm {

	void core_scene::scene_preupdate()
	{

		delete_enity();

		for (auto& i : m_entities)
		{
			for (auto comp : i->m_components_list) {

				if (!is_light_component(comp->m_component_type)) {
					comp->component_preupdate();
				}
			}
		}

		
	}
	
	void core_scene::scene_update(float delta_time, std::shared_ptr<core_gl_shader>& shader)
	{
		m_reloaded = false;
		int color_id = 0;

		for (auto& i : m_entities)
		{
			for (auto comp : i->m_components_list) {
				if (!is_light_component(comp->m_component_type)) {
					comp->component_update(delta_time, shader);
					shader->setInt("pick_color", color_id);
					++color_id;
				}
			}		
		}
	}
	
	void core_scene::scene_postupdate()
	{
		for (auto& i : m_entities)
		{
			for (auto comp : i->m_components_list) {

				if (!is_light_component(comp->m_component_type)) {
					comp->component_postupdate();
				}

			}
		}
	}

	unsigned int core_scene::total_component_count()
	{
		unsigned int total = 0;
		for (auto& i : m_entities)
			total += i->m_components_list.size();
	
		return total;
	}

	bool core_scene::does_ent_name_exist(std::string name)
	{
		bool does_exist = false;
		for (auto& i : m_entities)
			if (i->m_ent_ID == name) 
				does_exist = true;
		
		return does_exist;
	}


	std::shared_ptr<core_entity> core_scene::add_entity(std::shared_ptr<core_entity> entity) {
		m_entities.push_back(entity);
		return entity;
	}
	
	std::shared_ptr<core_entity> core_scene::add_entity(std::string entity_name)
	{
		auto ptr = std::make_shared<core_entity>(entity_name);
		m_entities.push_back(ptr);
		return ptr;
	}

	void core_scene::delete_enity()
	{
		if (m_destroy_list.empty())
			return;

		for (const auto& destroy_entity : m_destroy_list) {
			auto entity = get_entity_name(destroy_entity);
			if (entity)
			{
				m_entities.erase(std::find(m_entities.begin(), m_entities.end(), entity));
				m_reloaded;
			}
		}
		m_destroy_list.clear();
	}

	

	void core_scene::clear_entities()
	{
		m_reloaded = true;
		m_entities.clear();
		clear_selected_entities();
	}

	//--------------------------------------------------------- SERIALIZATION METHODS

	void core_scene::read_map_data(std::string file_path) {
		
		filedata::ZER read;
		read.read_file_cntx(file_path);
		current_scene = file_path;

		clear_entities();

		for (const auto& i : read.class_properties) {
			auto ent = add_entity(i.first);
			ent->read_saved_data("","", read);
		}
	}


	void core_scene::save_map_data(std::string path) {
		filedata::ZER read;

		for (const auto& e : m_entities) {
			e->save_data("", "", read);
		}

		if(current_scene.empty() || !path.empty())
		{
			read.save_file(read, path);
			current_scene = path;
		}
		else
			read.save_file(read, current_scene);
	}








	void core_scene::pre_update_light_components()
	{
		for (auto& i : m_entities)
		{
			for (auto& comp : i->m_components_list) {

				if (is_light_component(comp->m_component_type)) {
					comp->component_preupdate();
				}
			}
		}
	}

	void core_scene::update_light_components(float delta_time, std::shared_ptr<core_gl_shader>& shader)
	{
		for (auto& i : m_entities)
		{
			for (auto& comp : i->m_components_list) {
			
				if (is_light_component(comp->m_component_type)) {
					comp->component_update(delta_time, shader);				
				}
			}
		}
	}

	void core_scene::post_update_light_components()
	{
		for (auto& i : m_entities)
		{
			for (auto& comp : i->m_components_list) {

				if (is_light_component(comp->m_component_type)) {
					comp->component_postupdate();
				}
			}
		}
	}

}