#pragma once
#include "layer.h"
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "gl renderer/gl_renderer.h"

using namespace lowlevelsys;

namespace wizm {


	class scene_ui_layer : public core_layer {
	public:
		scene_ui_layer( gl_renderer* renderer);
		~scene_ui_layer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void update(float delta_time) override;

		void render_entity_node(core_entity* entity);
		void render_modify_popup();

	private:
		gl_renderer* m_renderer;
		bool skip_after_delete = false;
	};

}