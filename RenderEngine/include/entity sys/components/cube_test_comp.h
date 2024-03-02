#pragma once
#include "entity sys/component.h"
#include "gl core/vertex_buffer.h"
#include "gl core/core shader.h"
#include "system/material.h"

using namespace lowlevelsys;



namespace wizm {

	class cube_sm_component : public core_component {
	
	public:
		
		cube_sm_component();
		~cube_sm_component();


		void component_preupdate() override;
		void component_update() override;
		void component_postupdate() override;
		void test();

	public:

		core_arr_vertex_buffer* m_draw_data;
		core_gl_texture* m_texture;
		core_material* m_material;


		std::vector<float> vertices = {
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,

			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,

			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 0.0f
		};


		std::vector<unsigned int> indices = {
			0, 1, 2,  2, 3, 0,       // Back face
			4, 5, 6,  6, 7, 4,       // Front face
			8, 9, 10, 10, 11, 8,     // Left face
			12, 13, 14, 14, 15, 12,  // Right face
			16, 17, 18, 18, 19, 16,  // Bottom face
			20, 21, 22, 22, 23, 20   // Top face
		};



	};

}