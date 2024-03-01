#pragma once
#include <iostream>
#include "gl renderer/gl_renderer.h"

namespace wizm {

	class default_renderer {
	public:

		void render_setup(size_t window_size_x, size_t window_size_y, const char* window_name);
		void pre_render();
		void render();
		void post_render();

		inline default_renderer* get_renderer() {
			return this;
		}

	public:
		bool is_running = true;
		lowlevelsys::gl_renderer* m_gl_renderer;
	};


}
