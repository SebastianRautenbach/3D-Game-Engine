#pragma once
#include "entity sys/component.h"
#include "gl core/vertex_buffer.h"
#include "gl core/core shader.h"

using namespace lowlevelsys;



namespace wizm {

	class cube_sm_component : public core_component {
	
	public:
		
		cube_sm_component();
		~cube_sm_component();


		void component_preupdate() override;
		void component_update() override;
		void component_postupdate() override;


	public:
		
		core_gl_shader* shdr;
		core_arr_vertex_buffer* draw_data;
		core_gl_texture* texture;


		std::vector<float> vertices = {
			// Back face
			-1.0f, -1.0f, -1.0f, // Bottom-left
			 1.0f, -1.0f, -1.0f, // Bottom-right
			 1.0f,  1.0f, -1.0f, // Top-right
			-1.0f,  1.0f, -1.0f, // Top-left 
			// Front face
			-1.0f, -1.0f,  1.0f, // Bottom-left
			 1.0f, -1.0f,  1.0f, // Bottom-right
			 1.0f,  1.0f,  1.0f, // Top-right
			-1.0f,  1.0f,  1.0f  // Top-left
		};


		std::vector<unsigned int> indices = {
			// Back face
			0, 1, 2, // First Triangle
			2, 3, 0, // Second Triangle
			// Front face
			4, 5, 6, // First Triangle
			6, 7, 4, // Second Triangle
			// Left face
			4, 7, 3, // First Triangle
			3, 0, 4, // Second Triangle
			// Right face
			1, 5, 6, // First Triangle
			6, 2, 1, // Second Triangle
			// Bottom face
			0, 1, 5, // First Triangle
			5, 4, 0, // Second Triangle
			// Top face
			3, 2, 6, // First Triangle
			6, 7, 3  // Second Triangle
		};



	};

}