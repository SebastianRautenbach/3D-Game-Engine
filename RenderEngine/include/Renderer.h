#pragma once
#include <iostream>
#include "gl renderer/gl_renderer.h"
#include "scene.h"
#include "system/timer.h"
#include "input.h"

namespace wizm {

	class default_renderer {
	public:

		void render_setup(int window_size_x, int window_size_y, const char* window_name);
		void pre_render();
		void render();
		void post_render();


		inline default_renderer* get_renderer() {
			return this;
		}

	public:
		bool is_running = true;
		lowlevelsys::gl_renderer* m_gl_renderer;
		core_scene* m_scene;
		core_timer* m_timer;
		input_manager* m_input_manager;
	};


}
