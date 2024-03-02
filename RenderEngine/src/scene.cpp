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
	
	void core_scene::add_entity(std::string entity_name)
	{
		m_entities.push_back(new core_entity(entity_name));
	}
}