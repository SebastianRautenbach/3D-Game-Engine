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


		void read_saved_data(std::string parent_name, std::string index) override {
		
			filedata::ZER save_;
			save_.read_file_cntx();
		
			set_position(glm::vec3(
				save_[parent_name][index]["transform"].get_float("position")[0],
				save_[parent_name][index]["transform"].get_float("position")[1],
				save_[parent_name][index]["transform"].get_float("position")[2]
			));
			set_rotation(glm::vec3(
				save_[parent_name][index]["transform"].get_float("rotation")[0],
				save_[parent_name][index]["transform"].get_float("rotation")[1],
				save_[parent_name][index]["transform"].get_float("rotation")[2]
			));
			set_scale(glm::vec3(
				save_[parent_name][index]["transform"].get_float("scale")[0],
				save_[parent_name][index]["transform"].get_float("scale")[1],
				save_[parent_name][index]["transform"].get_float("scale")[2]
			));


			save_.save_file(save_);
		
		};


		void save_data(std::string parent_name, std::string index) const override {

			filedata::ZER save_;
			save_.read_file_cntx();

			save_[parent_name]["staticmesh" + index]["transform"].set_float("position", { get_position().x, get_position().y, get_position().z });
			save_[parent_name]["staticmesh" + index]["transform"].set_float("rotation", { get_rotation().x, get_rotation().y, get_rotation().z });
			save_[parent_name]["staticmesh" + index]["transform"].set_float("scale", { get_scale().x, get_scale().y, get_scale().z });


			save_.save_file(save_);


		}


	public:
		std::shared_ptr<staticmesh_asset> m_model;
		core_material* m_material;
		
		
		// test
		asset_manager* m_manager;
	};
}