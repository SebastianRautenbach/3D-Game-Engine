#pragma once
#include "layer.h"
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"


namespace wizm {
	class core_scene;

	class project_modifier : public core_layer {
	public:
		project_modifier(core_scene* scene);
		~project_modifier();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void update(float delta_time) override;

		core_scene* m_scene;
	};

}