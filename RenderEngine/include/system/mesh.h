#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <string>
#include <gl core/core shader.h>

#define MAX_BONE_INFLUENCE 4

struct vertex_draw_data {
	glm::vec3 Position;
	// normal
	glm::vec3 Normal;
	// texCoords
	glm::vec2 TexCoords;
	// tangent
	glm::vec3 Tangent;
	// bitangent
	glm::vec3 Bitangent;
	//bone indexes which will influence this vertex
	int m_BoneIDs[MAX_BONE_INFLUENCE];
	//weights from each bone
	float m_Weights[MAX_BONE_INFLUENCE];
};

struct Texture {
	unsigned int id;
	std::string type;
	std::string path;
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