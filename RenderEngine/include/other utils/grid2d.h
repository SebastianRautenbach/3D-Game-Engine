#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "system/3d_core_camera.h"
#include "gl core/vertex_buffer.h"
#include "gl core/core shader.h"
#include <vector>
#include <iostream>


namespace wizm {

	class core_grid {
	
	public:
		core_grid(core_3d_camera* camera);
		~core_grid() {draw_data->destroy_buffer();}
		
		void update_grid_pos();
		glm::vec3 get_grid_pos() { return position; }

		void draw_grid();
		
		std::vector<float> get_vertices() { return vertices; }
		std::vector<unsigned int> get_indices() { return indices; }

	
	private:

		glm::vec3 position;

		core_3d_camera* m_camera;

		core_arr_vertex_buffer* draw_data;

		core_gl_texture* texture;

	/*	core_gl_shader* shdr;*/


		std::vector<float> vertices = {
			// Positions         // Texture Coords
			-0.5f, 0.0f,  0.5f,  0.0f, 0.0f, // Top Left
			 0.5f, 0.0f,  0.5f,  1.0f, 0.0f, // Top Right
			 0.5f, 0.0f, -0.5f,  1.0f, 1.0f, // Bottom Right
			-0.5f, 0.0f, -0.5f,  0.0f, 1.0f  // Bottom Left
		};

		std::vector<unsigned int> indices = {
			 0, 1, 2, // First Triangle
			 2, 3, 0  // Second Triangle
		};


	};


}