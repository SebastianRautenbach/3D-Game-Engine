#pragma once
#include "entity sys/component.h"
#include "system/core_renderable.h"

using namespace lowlevelsys;

namespace wizm {

	class core_3d_camera;

	class camera_component : public core_component, public core_renderable {

	public:
		camera_component();
		~camera_component();

	public:
		void component_preupdate() override;
		void component_update() override;
		void component_postupdate() override;
		std::shared_ptr<core_component> _copy() const;


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
		
		}
		void save_data(std::string parent_name, std::string index, filedata::ZER& save_t) const override {
			save_t[parent_name]["cameracomponent" + index]["transform"].set_float("position", { get_position().x, get_position().y, get_position().z });
			save_t[parent_name]["cameracomponent" + index]["transform"].set_float("rotation", { get_rotation().x, get_rotation().y, get_rotation().z });
			save_t[parent_name]["cameracomponent" + index]["transform"].set_float("scale", { get_scale().x, get_scale().y, get_scale().z });
		}


	public:
		std::shared_ptr<core_3d_camera> m_camera;
		bool is_main_camera;
	};
}
