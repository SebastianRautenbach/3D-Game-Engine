#pragma once
#include <memory>
#include <string>

namespace wizm {

	class camera_core_3d;

	class camera_manager {
	public:
		camera_manager();
		~camera_manager();

		bool update_crnt_camera(bool simulate);


		void save_viewport_camera(std::string crnt_save_path);
		void load_save_viewport_camera(std::string crnt_save_path);

	public:
	
		std::shared_ptr<camera_core_3d> m_crnt_camera, m_viewport_camera;

	public:
		bool did_change_cam = false;
	};

}