#include "system/asset_manager.h"
#include "system/scene_manager.h"
#include "system/assets/texture_asset.h"
#include "system/assets/script_asset.h"

wizm::asset_manager::asset_manager()
{
	load_assets_db();
}

/*
	We basicly check if the component has an asset ID and if it does apply that asset 
	to the neccasary variable.
*/

void wizm::asset_manager::assign_assets()
{
	if(total_entities < global_scene->m_entities.size() || global_scene->m_reloaded)
	{
		for (auto& ent : global_scene->m_entities) {
			for (auto& comp : ent->m_components_list)
			{
				auto mesh_comps = std::dynamic_pointer_cast<staticmesh_component>(comp);
				if (mesh_comps)
				{
					if (m_assets[mesh_comps->m_asset_id])
					{
					
						mesh_comps->m_model = load<staticmesh_asset>(mesh_comps->m_asset_id, "");
			
						
						if(!mesh_comps->m_material->diffuse_asset_id.empty() && get_asset_details_from_id(mesh_comps->m_material->diffuse_asset_id).type == tTEXTURE &&
							!get_asset_details_from_id(mesh_comps->m_material->diffuse_asset_id).path.empty()
							)
						{
							mesh_comps->m_material->m_texture_n[0] = load<texture_asset>(mesh_comps->m_material->diffuse_asset_id, "");
						}
							
						if (!mesh_comps->m_material->specular_asset_id.empty() && get_asset_details_from_id(mesh_comps->m_material->specular_asset_id).type == tTEXTURE &&
							!get_asset_details_from_id(mesh_comps->m_material->specular_asset_id).path.empty()
							)
						{
							mesh_comps->m_material->m_texture_n[1] = load<texture_asset>(mesh_comps->m_material->specular_asset_id, "");
						}
					}					
				}
				mesh_comps.reset();

				auto script_comp = std::dynamic_pointer_cast<scripting_component>(comp);
				if (script_comp) {
					script_comp->m_script_asset = load<script_asset>(script_comp->script_asset_id, "");
				}
				script_comp.reset();
			}
		}

		total_entities = global_scene->m_entities.size();
	}


}

void wizm::asset_manager::load_assets_db()
{
	auto assets = asset_import.retrieve_all_assets();

	for (const auto& asset : assets) {
		if (asset.type == tMESH) {
			load<staticmesh_asset>(asset.id, asset.path);
		}
		else if (asset.type == tTEXTURE) {
			load<texture_asset>(asset.id, asset.path);
		}
		else if (asset.type == tSCRIPT) {
			load<script_asset>(asset.id, asset.path);
		}
	}
}
