#pragma once
#include "scene.h"


namespace wizm {

	class camera_core_3d;

	class camera_manager {
	public:
		camera_manager(core_scene* scene);
		~camera_manager();

		bool update_crnt_camera(bool simulate);


	public:
		core_scene* m_scene;

		std::shared_ptr<camera_core_3d> m_crnt_camera, m_viewport_camera;

	private:
		bool did_change_cam = false;
	};

}