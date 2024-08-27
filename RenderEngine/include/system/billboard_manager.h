#pragma once
#include "billboard.h"
#include "scene.h"


namespace wizm {

	class billboard_manager {
	public:
		
		billboard_manager(core_scene* scene, std::shared_ptr<core_gl_shader> shader);
		void render();


	public:
		glm::vec3 color_tint = glm::vec3(1.0);
		billboard_core* m_billboard_core;
		core_scene* m_scene;
		std::shared_ptr<core_gl_shader> m_shader;
	};

}