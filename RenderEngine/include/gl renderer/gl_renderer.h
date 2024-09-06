#pragma once 
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "input.h"
#include "gl core/vertex_buffer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "scene.h"
#include "system/camera_manager.h"


using namespace wizm;

namespace lowlevelsys {

	class gl_renderer {
	public:
		void setup(int window_size_x, int window_size_y, const char* window_name, core_scene* scene, std::shared_ptr<camera_manager> camera_manager);
		
		void pre_render(bool& is_running, float deltaTime);
		void render(float deltaTime);
		void post_render(float deltaTime);
		void update_draw_data();
		void on_exit();

	public:
		GLFWwindow* window;
		input_manager* m_input_manager;
		
		std::vector<std::shared_ptr<core_gl_shader>> m_shdrs;

		core_scene* m_scene;
		std::shared_ptr<camera_manager> m_camera_manager;
		

	public:
		int w_width, w_height;

	private:
		unsigned int shader_count = 0;
	};
}
