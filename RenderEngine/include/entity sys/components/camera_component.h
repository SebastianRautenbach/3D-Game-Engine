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


		void read_saved_data(std::string parent_name, std::string index, filedata::ZER& save_t) override {}
		void save_data(std::string parent_name, std::string index, filedata::ZER& save_t) const override {}


	public:
		std::shared_ptr<core_3d_camera> m_camera;
		bool is_main_camera;
	};
}
