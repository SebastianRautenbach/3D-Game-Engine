#include "system/core_mesh.h"

wizm::core_mesh::core_mesh(std::vector<vertex_draw_data> vertices, std::vector<unsigned int> indices, std::vector<core_gl_texture> textures)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;
	setup_mesh();
}

void wizm::core_mesh::draw_mesh()
{
}

void wizm::core_mesh::setup_mesh()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertex_draw_data), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
        &indices[0], GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_draw_data), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_draw_data), (void*)offsetof(vertex_draw_data, Normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_draw_data), (void*)offsetof(vertex_draw_data, TexCoords));

    glBindVertexArray(0);

    vertec_arr = new core_arr_vertex_buffer(vertices[0], indices);
    vertec_arr->create_attrib_arr(0, 3, 8 * sizeof(float), 0);
    vertec_arr->create_attrib_arr(1, 2, 8 * sizeof(float), (3 * sizeof(float)));
    vertec_arr->create_attrib_arr(2, 3, 8 * sizeof(float), (5 * sizeof(float)));
    vertec_arr->create_buffer();
}
