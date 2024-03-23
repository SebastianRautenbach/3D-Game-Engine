#pragma once
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

namespace wizm {

	class gui_layer {
	public:
		gui_layer(GLFWwindow* window);
		~gui_layer();
		void pre_update();
		void update();
		void post_update();
		void render_viewport(uint64_t textureID, unsigned int width, unsigned int height);
	
	private:
		bool show_demo_window = true;
		ImVec2 m_window_size;
	};


}