#pragma once
#include "entity sys/component.h"
#include "system/core_model.h"
#include "system/material.h"
#include "system/assets/mesh_asset.h"

using namespace lowlevelsys;

namespace wizm {
	class staticmesh_component : public core_component {
	
	public:
		
		staticmesh_component(const char* file_path);
		staticmesh_component(std::shared_ptr<staticmesh_asset> mesh);
		~staticmesh_component();
		
		void component_preupdate() override;
		void component_update() override;
		void component_postupdate() override;

		void change_mesh(const char* file_path);


	public:
		std::shared_ptr<staticmesh_asset> m_model;
		core_material* m_material;
	};
}