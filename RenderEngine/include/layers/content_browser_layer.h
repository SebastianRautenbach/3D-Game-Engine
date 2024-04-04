#pragma once
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "layer.h"
#include "gl core/core shader.h"
#include "system/asset_manager.h"

namespace wizm { 
	
	
	class content_browser_layer : public core_layer
	{
	public:
		content_browser_layer();
		~content_browser_layer();
	
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void update(float delta_time) override;
	


	public:

		core_gl_texture* texture_test;
		asset_manager asset_manager;
	}; 


}
