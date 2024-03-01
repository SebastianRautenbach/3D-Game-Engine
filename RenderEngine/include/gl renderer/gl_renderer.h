#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "input.h"
#include "gl core/vertex_buffer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "system/3d_core_camera.h"
#include "system/timer.h"
#include "other utils/grid2d.h"
#include "entity sys/components/cube_test_comp.h"

using namespace wizm;

namespace lowlevelsys {
	class gl_renderer {
	public:
		void setup(size_t window_size_x, size_t window_size_y, const char* window_name);
		void pre_render(bool& is_running);
		void render();
		void post_render();
		void on_exit();

	public:
		GLFWwindow* window;
		input_manager* m_input_manager;
		core_gl_shader* shdr;
		core_grid* grid2d;
		core_3d_camera* camera;
		glm::mat4 trans;
		core_timer* timer;
		core_grid* grid;
		cube_sm_component* test_cube;

	public:
		int w_width, w_height;
	};
}
