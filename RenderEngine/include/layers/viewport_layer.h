#pragma once
#include "layer.h"
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "ImGuizmo/ImGuizmo.h"
#include "system/draw_ray.h"
#include "layers/UI/popup_window.h"
#include "system/camera_manager.h"
#include "gl renderer/gl_renderer.h"

using namespace lowlevelsys;

namespace wizm {

	class core_entity;

	class viewport_layer : public core_layer {
	public:
		viewport_layer(unsigned int fbID, std::shared_ptr<camera_manager> camera_manager, gl_renderer* renderer);
		~viewport_layer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void update(float delta_time) override;

		void scene_viewport_func();

		void get_mouse_pick(bool multi_select);
		void properties_mouse_pick(bool multi_select);
		std::shared_ptr<core_entity> get_ent_pick(glm::vec3 ray_dir, glm::vec3 ray_pos);
		std::shared_ptr<core_entity> get_ent_pick_angle(glm::vec3 ray_dir, glm::vec3 ray_pos);

	private:
		unsigned int m_fbID;
		std::shared_ptr<camera_manager> m_camera_manager;
		float m_snap_value = 0.5f;
		bool m_should_snap = false;
		gl_renderer* m_renderer;
		bool is_global_gizmo = false;
		int guizmo_type = 0;
		ImVec2 mSize;
	};

}