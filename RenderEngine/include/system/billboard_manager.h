#pragma once
#include "billboard.h"
#include "scene.h"


namespace wizm {

	class billboard_manager {
	public:
		
		billboard_manager(core_scene* scene, std::shared_ptr<core_gl_shader> shader);
		void render();


	public:
		billboard_core* m_billboard_core;
		core_scene* m_scene;
		std::shared_ptr<core_gl_shader> m_shader;
	};

}