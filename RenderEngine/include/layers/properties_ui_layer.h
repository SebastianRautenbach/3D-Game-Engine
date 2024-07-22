#pragma once
#include "layer.h"
#include "gl renderer/gl_renderer.h"
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "scene.h"


namespace wizm {

	class asset_manager;

	class properties_ui_layer : public core_layer {

	public:
		properties_ui_layer(core_scene* scene, gl_renderer* renderer, asset_manager* manager);
		~properties_ui_layer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void update(float delta_time) override;

		// properties panel specific
		
		void component_add_popup(core_entity* select_ent);
		void modify_component_attrib(std::string& type, std::shared_ptr<core_component> component);

	private:
		core_scene* m_scene;
		gl_renderer* m_renderer;
		asset_manager* m_asset_manager;
	};


}