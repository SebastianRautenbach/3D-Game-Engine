#include "system/asset_manager.h"
#include "entity sys/entity.h"

wizm::asset_manager::asset_manager(std::vector<core_entity*>* entities)
	:	m_entities(entities)
{
}

void wizm::asset_manager::assign_assets()
{

	if(total_entities < m_entities->size())
	{
		for (auto& ent : *m_entities) {
			for (auto& comp : ent->m_components_list)
			{
				auto mesh_comps = std::dynamic_pointer_cast<staticmesh_component>(comp);
				if (mesh_comps)
				{
					mesh_comps->m_model = load<staticmesh_asset>(mesh_comps->m_asset_id,"");
				}
			}
		}

		total_entities = m_entities->size();
	}


}
