#pragma once
#include "entity sys/component.h"
#include "system/core_model.h"
#include "system/material.h"
#include "system/assets/mesh_asset.h"
#include "system/asset_manager.h"

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


		//////////////////////////////////////////////////
		//////////  SERIALIZATION METHOD /////////////////
		//////////////////////////////////////////////////


		void read_saved_data(std::string parent_name, std::string index) const override {};


		void save_data(std::string parent_name, std::string index) const override {

			filedata::ZER save_;
			save_.read_file_cntx();

			save_[parent_name]["staticmesh" + index]["transform"]["position"].set_float("x", { get_position().x });
			save_[parent_name]["staticmesh" + index]["transform"]["position"].set_float("y", { get_position().y });
			save_[parent_name]["staticmesh" + index]["transform"]["position"].set_float("z", { get_position().z });

			save_[parent_name]["staticmesh" + index]["transform"]["rotation"].set_float("x", { get_rotation().x });
			save_[parent_name]["staticmesh" + index]["transform"]["rotation"].set_float("y", { get_rotation().y });
			save_[parent_name]["staticmesh" + index]["transform"]["rotation"].set_float("z", { get_rotation().z });

			save_[parent_name]["staticmesh" + index]["transform"]["scale"].set_float("x", { get_scale().x });
			save_[parent_name]["staticmesh" + index]["transform"]["scale"].set_float("y", { get_scale().y });
			save_[parent_name]["staticmesh" + index]["transform"]["scale"].set_float("z", { get_scale().z });


			save_.save_file(save_);


		}


	public:
		std::shared_ptr<staticmesh_asset> m_model;
		core_material* m_material;
		
		
		// test
		asset_manager* m_manager;
	};
}