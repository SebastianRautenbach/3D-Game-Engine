#pragma once
#include "scene.h"


namespace wizm {

	class core_3d_camera;

	class camera_manager {
	public:
		camera_manager(core_scene* scene);
		~camera_manager();

		void update_crnt_camera(bool simulate);


	public:
		core_scene* m_scene;

		std::shared_ptr<core_3d_camera> m_crnt_camera, m_viewport_camera;
	};

}