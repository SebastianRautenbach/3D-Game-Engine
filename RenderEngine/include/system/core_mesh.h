#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <string>
#include <gl core/core shader.h>
#include "gl core/vertex_buffer.h"



namespace wizm {
	class core_mesh {
	
	public:
		core_mesh(std::vector<vertex_data> vertices, std::vector<unsigned int> indices, std::vector<core_gl_texture> textures);
		void draw_mesh();
		core_gl_shader* m_shader;
	
	public:
		std::vector<vertex_data> vertices;
		std::vector<unsigned int> indices;
		std::vector<core_gl_texture> textures;

	private:
		core_arr_vertex_buffer* vertex_arr;
		void setup_mesh();
	};
}