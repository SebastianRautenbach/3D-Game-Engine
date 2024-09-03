#pragma once
#include "layer.h"
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "gl renderer/gl_renderer.h"
#include "system/camera_manager.h"

namespace wizm {

	class scene_viewport_layer : public core_layer {

	public:

		scene_viewport_layer(std::shared_ptr<camera_manager> camera_manager);
		~scene_viewport_layer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void update(float delta_time) override;


	public:
		std::shared_ptr<camera_manager> m_camera_manager;
	};

}