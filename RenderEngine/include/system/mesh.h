#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <string>
#include <gl core/core shader.h>

struct vertex_draw_data {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture {
	unsigned int id;
	std::string type;
};



class Mesh {
public:
	// mesh data
	std::vector<vertex_draw_data> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture>      textures;

	Mesh(std::vector<vertex_draw_data> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	void Draw(core_gl_shader& shader);

private:
	//  render data
	unsigned int VAO, VBO, EBO;

	void setupMesh();
};