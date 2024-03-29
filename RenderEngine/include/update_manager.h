#pragma once
#include <iostream>
#include "gl renderer/gl_renderer.h"
#include "scene.h"
#include "system/timer.h"
#include "input.h"
#include "system/asset_manager.h"
#include "layers/gui_cntx.h"
#include "layers/layerstack.h"
#include "layers/viewport_layer.h"
#include "layers/scene_ui_layer.h"

namespace wizm {

	class update_manager {
	public:

		void render_setup(int window_size_x, int window_size_y, const char* window_name);
		void pre_render();
		void render();
		void post_render();


		inline update_manager* get_renderer() {
			return this;
		}

	public:
		bool is_running = true;
		lowlevelsys::gl_renderer* m_gl_renderer;
		core_scene* m_scene;
		core_timer* m_timer;
		input_manager* m_input_manager;
		gui_layer* layer;
		core_framebuffer* m_framebuffer;
		layer_stack* m_layer_stack;

		// new system
	};


}
