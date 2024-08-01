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

		staticmesh_component();
		staticmesh_component(std::shared_ptr<staticmesh_asset> mesh);
		~staticmesh_component();

		void component_preupdate() override;
		void component_update() override;
		void component_postupdate() override;
		std::shared_ptr<core_component> _copy() const;


		std::pair<glm::vec3, glm::vec3> get_bounding_box() const;


		//////////////////////////////////////////////////
		//////////  SERIALIZATION METHOD /////////////////
		//////////////////////////////////////////////////


		void read_saved_data(std::string parent_name, std::string index, filedata::ZER& save_t) override {


			set_position(glm::vec3(
				save_t[parent_name][index]["transform"].get_float("position")[0],
				save_t[parent_name][index]["transform"].get_float("position")[1],
				save_t[parent_name][index]["transform"].get_float("position")[2]
			));
			set_rotation(glm::vec3(
				save_t[parent_name][index]["transform"].get_float("rotation")[0],
				save_t[parent_name][index]["transform"].get_float("rotation")[1],
				save_t[parent_name][index]["transform"].get_float("rotation")[2]
			));
			set_scale(glm::vec3(
				save_t[parent_name][index]["transform"].get_float("scale")[0],
				save_t[parent_name][index]["transform"].get_float("scale")[1],
				save_t[parent_name][index]["transform"].get_float("scale")[2]
			));

			m_asset_id = save_t[parent_name][index].get_string("asset id")[0];
			m_material->diffuse_asset_id = save_t[parent_name][index]["material"].get_string("diffuse_asset_id")[0];
			m_material->specular_asset_id = save_t[parent_name][index]["material"].get_string("specular_asset_id")[0];

		};


		void save_data(std::string parent_name, std::string index, filedata::ZER& save_t) const override {

			save_t[parent_name]["staticmesh" + index]["transform"].set_float("position", { get_position().x, get_position().y, get_position().z });
			save_t[parent_name]["staticmesh" + index]["transform"].set_float("rotation", { get_rotation().x, get_rotation().y, get_rotation().z });
			save_t[parent_name]["staticmesh" + index]["transform"].set_float("scale", { get_scale().x, get_scale().y, get_scale().z });

			save_t[parent_name]["staticmesh" + index].set_string("asset id", { m_asset_id });
			save_t[parent_name]["staticmesh" + index]["material"].set_string("diffuse_asset_id", { m_material->diffuse_asset_id });
			save_t[parent_name]["staticmesh" + index]["material"].set_string("specular_asset_id", { m_material->specular_asset_id });


		}


	public:
		std::shared_ptr<staticmesh_asset> m_model;
		std::unique_ptr<core_material> m_material;
		std::string m_asset_id;
	};
}