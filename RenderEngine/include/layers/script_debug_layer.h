#pragma once
#include "layer.h"
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"

namespace wizm {

	class asset_manager;

	class script_debug_layer : public core_layer {
	public:
		script_debug_layer();
		~script_debug_layer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void update(float delta_time) override;

	private:
	};

}