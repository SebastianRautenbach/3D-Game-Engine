#pragma once
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include "system/3d_core_camera.h"
#include "layer.h"

namespace wizm {

	class gui_layer : public core_layer
	{
	public:
		gui_layer(GLFWwindow* window);
		~gui_layer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;


		void begin();
		void end();
		
	
	private:
		bool show_demo_window = true;
		ImVec2 m_window_size;
		GLFWwindow* m_window;
	};


}