#include "system/asset_manager.h"
#include "scene.h"

wizm::asset_manager::asset_manager(core_scene* scene)
	:	m_scene(scene)
{
}

void wizm::asset_manager::assign_assets()
{

	if(total_entities < m_scene->m_entities.size() || m_scene->m_reloaded)
	{
		for (auto& ent : m_scene->m_entities) {
			for (auto& comp : ent->m_components_list)
			{
				auto mesh_comps = std::dynamic_pointer_cast<staticmesh_component>(comp);
				if (mesh_comps)
				{
					mesh_comps->m_model = load<staticmesh_asset>(mesh_comps->m_asset_id,"");
				}
			}
		}

		total_entities = m_scene->m_entities.size();
	}


}
