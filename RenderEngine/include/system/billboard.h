#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "node.h"
#include "gl core/core shader.h"
#include <string>
#include <vector>

namespace wizm {

	enum eBillboardType {
		eLight,
		ePartical
	};

	struct billboard_s {
		eBillboardType eBillboard;
		core_gl_texture texture;
		core_gl_shader shader;
	};

	class billboard_core : public core_node {
	public:
		billboard_core();
		void pre_update();
		void update();
		void post_update();



	public:
		std::vector<billboard_s> m_billboards;

		float vertices[20] = {
			// Positions       // Texture Coords
			 0.5f,  0.5f, 0.0f,  1.0f, 1.0f,   // Top Right
			 0.5f, -0.5f, 0.0f,  1.0f, 0.0f,   // Bottom Right
			-0.5f, -0.5f, 0.0f,  0.0f, 0.0f,   // Bottom Left
			-0.5f,  0.5f, 0.0f,  0.0f, 1.0f    // Top Left 
		};
		unsigned int indices[6] = {
			0, 1, 3,   // First triangle
			1, 2, 3    // Second triangle
		};

		unsigned int VBO, VAO, EBO;

	};


}