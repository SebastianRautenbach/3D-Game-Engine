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
	
	core_entity& core_scene::add_entity(std::string entity_name)
	{
		auto ptr = new core_entity(entity_name);
		m_entities.push_back(ptr);
		return *ptr;
	}

	void core_scene::clear_entities()
	{
		m_reloaded = true;
		for (auto& ent : m_entities)
			delete ent;
		m_entities.clear();
		set_crnt_entity(nullptr);
	}

	//--------------------------------------------------------- SERIALIZATION METHODS

	void core_scene::read_map_data() {
		
		filedata::ZER read;
		read.read_file_cntx("GAME/Content/levels/level1.zer");

		clear_entities();

		for (const auto& i : read.class_properties) {
			auto& ent = add_entity(i.first);
			ent.read_saved_data("","", read);
		}
	}


	void core_scene::save_map_data() {
		filedata::ZER read;

		for (const auto& e : m_entities) {
			e->save_data("", "", read);
		}

		read.save_file(read);
	}
}