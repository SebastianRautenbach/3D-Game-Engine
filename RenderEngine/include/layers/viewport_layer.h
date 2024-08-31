#pragma once
#include "layer.h"
#include "system/3d_core_camera.h"
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "ImGuizmo/ImGuizmo.h"
#include "scene.h"
#include "system/draw_ray.h"
#include "gl renderer/gl_renderer.h"
#include "layers/UI/popup_window.h"

namespace wizm {


	class viewport_layer : public core_layer {
	public:
		viewport_layer(unsigned int fbID, std::shared_ptr<core_3d_camera> camera, core_scene* scene, gl_renderer* renderer);
		~viewport_layer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void update(float delta_time) override;

		void get_mouse_pick();
		void properties_mouse_pick();
		std::shared_ptr<core_entity> get_ent_pick(glm::vec3 ray_dir, glm::vec3 ray_pos);
		std::shared_ptr<core_entity> get_ent_pick_angle(glm::vec3 ray_dir, glm::vec3 ray_pos);

	private:
		unsigned int m_fbID;
		std::shared_ptr<core_3d_camera> m_camera;
		float m_snap_value = 0.5f;
		bool m_should_snap = false;
		gl_renderer* m_renderer;

		// needs to be a better way :(
		core_scene* m_scene;
	};

}