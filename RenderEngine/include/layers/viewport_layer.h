#pragma once
#include "layer.h"
#include "system/3d_core_camera.h"
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "ImGuizmo/ImGuizmo.h"
#include "scene.h"

namespace wizm {


	class viewport_layer : public core_layer {
	public:
		viewport_layer(unsigned int fbID, core_3d_camera* camera, core_scene* scene);
		~viewport_layer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void update() override;

	private:
		unsigned int m_fbID;
		core_3d_camera* m_camera;

		// needs to be a better way :(
		core_scene* m_scene;
	};

}