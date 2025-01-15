#include "scene.h"
#include <functional>

namespace wizm {

	void core_scene::scene_preupdate()
	{

		//delete_enity(nullptr);

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
		for (auto& i : m_entities)
		{
			for (auto comp : i->m_components_list) {
				if (!is_light_component(comp->m_component_type)) {
					comp->component_update(delta_time, shader);
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


	core_entity* core_scene::add_entity(core_entity* entity) {
		m_entities.push_back(entity);
		return entity;
	}
	
	core_entity* core_scene::add_entity(std::string entity_name)
	{
		auto ptr = new core_entity(entity_name);
		m_entities.push_back(ptr);
		return ptr;
	}


	void core_scene::delete_enity(core_entity* entity)
	{
		if (entity == NULL) { return; }
		
		
		// clear all entities with the same parent from the entity list to ensure that a call to a nullptr isn't made.
		for (auto& child : entity->get_children()) {		
			std::function<void(core_entity*)> go_to_child = [&](core_entity* pchild) {

				if (!pchild) { return nullptr; }

				for (auto& c : pchild->get_children()) {
					go_to_child(dynamic_cast<core_entity*>(c));
				}

				m_entities.erase(std::find(m_entities.begin(), m_entities.end(), pchild));				
			};

			go_to_child(dynamic_cast<core_entity*>(child));
		}
		
		m_entities.erase(std::find(m_entities.begin(), m_entities.end(), entity));
		delete entity;
	}

	void core_scene::delete_all_entities()
	{
		std::vector<core_entity*> deleted_ents;

		for (auto& ent : m_entities) {
			bool is_simular = false;


			for (auto& del_ent : deleted_ents) {
				if (ent == del_ent) {
					is_simular = true;
				}
			}

			if (is_simular) { continue; }

			if (ent->get_children().empty())
			{
				delete ent;
			}
			else
			{
				for(auto& child : ent->get_children())
					deleted_ents.emplace_back((core_entity*)child);
				
				delete ent;
			}
		}
		deleted_ents.clear();
		m_entities.clear();
	}

	

	void core_scene::clear_entities()
	{
		m_reloaded = true;
		delete_all_entities();
		clear_selected_entities();
	}

	//--------------------------------------------------------- SERIALIZATION METHODS

	void core_scene::read_map_data(std::string file_path) {
		
		filedata::ZER read;
		read.read_file_cntx(file_path);
		current_scene = file_path;

		clear_entities();

		for (const auto& i : read.class_properties) {
			
			if (!read[i.first]["specs"].get_int("is_entity")[0])
				continue;

			auto ent = add_entity(i.first);
			ent->read_saved_data("","", read);
		}
	}


	void core_scene::save_map_data(std::string path) {
		filedata::ZER read;

		for (const auto& e : m_entities) {
			read[e->m_ent_ID]["specs"].set_int("is_entity", {1});
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