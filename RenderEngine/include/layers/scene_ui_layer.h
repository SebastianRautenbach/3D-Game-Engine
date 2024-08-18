#pragma once
#include "scene.h"
#include "layer.h"
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "gl renderer/gl_renderer.h"

namespace wizm {


	class scene_ui_layer : public core_layer {
	public:
		scene_ui_layer(core_scene* scene, gl_renderer* renderer);
		~scene_ui_layer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void update(float delta_time) override;

	private:
		core_scene* m_scene;
		gl_renderer* m_renderer;
	};

}