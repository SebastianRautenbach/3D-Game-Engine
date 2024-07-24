#include "system/asset_manager.h"
#include "scene.h"
#include "system/assets/texture_asset.h"

wizm::asset_manager::asset_manager(core_scene* scene)
	:	m_scene(scene)
{
	load_assets_db();
}

/*
	We basicly check if the component has an asset ID and if it does apply that asset 
	to the neccasary variable.
*/

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
					if (m_assets[mesh_comps->m_asset_id])
					{
						mesh_comps->m_model = load<staticmesh_asset>(mesh_comps->m_asset_id, "");
						mesh_comps->m_material->m_texture_n.clear();
						
						if(!mesh_comps->m_material->diffuse_asset_id.empty())
							mesh_comps->m_material->m_texture_n.emplace_back(load<texture_asset>(mesh_comps->m_material->diffuse_asset_id, ""));
						if(!mesh_comps->m_material->specular_asset_id.empty())
							mesh_comps->m_material->m_texture_n.emplace_back(load<texture_asset>(mesh_comps->m_material->specular_asset_id, ""));
					}
					else {                            		//---------------------------------------------- I DONT LIKE THIS APPROACH
															//---------------------------------------------- 
						for (auto& asset : m_assets) {
							if (asset.second == mesh_comps->m_model) {
								mesh_comps->m_asset_id = asset.first;
							}
						}
					}
				}
			}
		}

		total_entities = m_scene->m_entities.size();
	}


}

void wizm::asset_manager::load_assets_db()
{
	auto assets = asset_import.retrieve_all_assets();

	for (const auto& asset : assets) {
		if (asset.type == tMESH) {
			load<staticmesh_asset>(asset.id, asset.path);
		}
		if (asset.type == tTEXTURE) {
			load<texture_asset>(asset.id, asset.path);
		}
	}
}
