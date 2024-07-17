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
	
	core_entity& core_scene::add_entity(std::string entity_name)
	{
		auto ptr = new core_entity(entity_name);
		m_entities.push_back(ptr);
		return *ptr;
	}

	//--------------------------------------------------------- SERIALIZATION METHODS

	void core_scene::read_map_data() {
		
		filedata::ZER read;
		read.read_file_cntx();

		for (const auto& i : read.class_properties) {
			
			bool does_exist = false;
			for (auto& y : m_entities) {
				if (y->m_ent_ID == i.first)
					does_exist = true;
			}
			if(!does_exist)
			{
				auto& ent = add_entity(i.first);
				ent.read_saved_data("","");
			}
		}
	}


	void core_scene::save_map_data() {
		for (const auto& e : m_entities) {
			e->save_data("", "");
		}
	}
}