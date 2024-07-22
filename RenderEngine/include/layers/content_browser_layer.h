#pragma once
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "layer.h"
#include "gl core/core shader.h"
#include "system/asset_manager.h"
#include "system/filewatcher.h"
#include "system/asset_importer.h"

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

		filewatcher* watcher;
		asset_importer asset_import;
		std::vector<asset_details> assets;
		//asset_manager asset_manager;
	}; 


}
