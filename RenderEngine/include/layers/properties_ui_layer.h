#pragma once
#include "layer.h"
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "scene.h"


namespace wizm {

	class properties_ui_layer : public core_layer {

	public:
		properties_ui_layer(core_scene* scene);
		~properties_ui_layer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void update() override;

	private:
		core_scene* m_scene;

	};


}