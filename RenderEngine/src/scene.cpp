#include "scene.h"


namespace wizm {
	
	void core_scene::scene_preupdate()
	{
		for (auto& i : m_entities)
		{
			i->entity_preupdate();
		}

		
	}
	
	void core_scene::scene_update()
	{
		m_reloaded = false;

		for (auto& i : m_entities)
		{
			i->entity_update();
		}
	}
	
	void core_scene::scene_postupdate()
	{
		for (auto& i : m_entities)
		{
			i->entity_postupdate();
		}


	}

	unsigned int core_scene::total_component_count()
	{
		unsigned int total = 0;
		for (auto& i : m_entities)
			total += i->m_components_list.size();
	
		return total;
	}
	
	std::shared_ptr<core_entity> core_scene::add_entity(std::string entity_name)
	{
		auto ptr = std::make_shared<core_entity>(entity_name);
		m_entities.push_back(ptr);
		return ptr;
	}

	void core_scene::clear_entities()
	{
		m_reloaded = true;
		m_entities.clear();
		set_crnt_entity(nullptr);
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
}