#pragma once
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "layer.h"
#include "gl core/core shader.h"
#include "system/asset_manager.h"
#include "system/filewatcher.h"
#include "system/asset_importer.h"
#include "gl core/core shader.h"

namespace wizm { 
	
	
	class content_browser_layer : public core_layer
	{
	public:
		content_browser_layer();
		~content_browser_layer();
	
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void update(float delta_time) override;
		
		std::vector<std::filesystem::path> get_directory_content(const std::filesystem::path& path);

	public:

		filewatcher* watcher;
		asset_importer asset_import;
		std::vector<asset_details> assets;
		std::filesystem::path current_directory = "GAME";
		core_gl_texture* folder_file_texture;
		core_gl_texture* mesh_file_icon;
		core_gl_texture* file_texture;
		core_gl_texture* image_file_icon;
		core_gl_texture* map_file_icon;
	}; 


}
