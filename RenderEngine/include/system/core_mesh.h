#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <string>
#include <gl core/core shader.h>
#include "gl core/vertex_buffer.h"

struct vertex_draw_data {
	glm::vec3 Position;

	glm::vec3 Normal;
	
	glm::vec2 TexCoords;
	
	glm::vec3 Tangent;
	
	glm::vec3 Bitangent;
	
	int m_BoneIDs[4];

	float m_Weights[4];
};

namespace wizm {
	class core_mesh {
	
	public:
		core_mesh(std::vector<vertex_draw_data> vertices, std::vector<unsigned int> indices, std::vector<core_gl_texture> textures);
		void draw_mesh();
	
	
	public:
		std::vector<vertex_draw_data> vertices;
		std::vector<unsigned int> indices;
		std::vector<core_gl_texture> textures;

	private:
		core_arr_vertex_buffer* vertec_arr;
		void setup_mesh();
	};
}