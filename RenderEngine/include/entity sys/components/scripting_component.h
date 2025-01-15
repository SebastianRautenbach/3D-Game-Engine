#pragma once
#include "entity sys/component.h"
#include "other utils/common.h"
#include "system/assets/script_asset.h"

using namespace lowlevelsys;

namespace wizm {

	class scripting_component : public core_component {


	public:
		
		scripting_component();
		~scripting_component();
		
		
		void component_preupdate() override;
		void component_update(float delta_time, std::shared_ptr<core_gl_shader>& shader) override;
		void component_postupdate() override;
		core_component* _copy() const;


		void read_saved_data(std::string parent_name, std::string index, filedata::ZER& save_t) override {
			set_position(glm::vec3(
				save_t[index]["transform"].get_float("position")[0],
				save_t[index]["transform"].get_float("position")[1],
				save_t[index]["transform"].get_float("position")[2]
			));
			set_rotation(glm::vec3(
				save_t[index]["transform"].get_float("rotation")[0],
				save_t[index]["transform"].get_float("rotation")[1],
				save_t[index]["transform"].get_float("rotation")[2]
			));
			set_scale(glm::vec3(
				save_t[index]["transform"].get_float("scale")[0],
				save_t[index]["transform"].get_float("scale")[1],
				save_t[index]["transform"].get_float("scale")[2]
			));

			script_asset_id = save_t[index].get_string("script_asset_id")[0];
		}

		void save_data(std::string parent_name, std::string index, filedata::ZER& save_t) const override {
			save_t["ScriptingComponent" + index]["transform"].set_float("position", { get_position().x, get_position().y, get_position().z });
			save_t["ScriptingComponent" + index]["transform"].set_float("rotation", { get_rotation().x, get_rotation().y, get_rotation().z });
			save_t["ScriptingComponent" + index]["transform"].set_float("scale", { get_scale().x, get_scale().y, get_scale().z });

			save_t["ScriptingComponent" + index].set_string("script_asset_id", { script_asset_id });
		}		

	public:
		std::string script_asset_id;
		std::shared_ptr<script_asset> m_script_asset = nullptr;

	};


}