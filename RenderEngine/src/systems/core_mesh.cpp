#include "system/core_mesh.h"

lowlevelsys::core_mesh::core_mesh(std::vector<vertex_data> vertices, std::vector<unsigned int> indices, std::vector<core_gl_texture> textures)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;
	setup_mesh();
}

void lowlevelsys::core_mesh::draw_mesh(core_gl_shader* shader)
{
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;

    
    vertex_arr->draw_buffer(static_cast<unsigned int>(indices.size()));


  
    glActiveTexture(GL_TEXTURE0);
}

void lowlevelsys::core_mesh::setup_mesh()
{
    vertex_arr = new core_arr_vertex_buffer(vertices, indices);
    vertex_arr->bind_buffer();
    
    vertex_arr->create_attrib_arr(0, 3, sizeof(vertex_data), 0); // pos
    vertex_arr->create_attrib_arr(1, 3, sizeof(vertex_data), offsetof(vertex_data, Normal)); // normal
    vertex_arr->create_attrib_arr(2, 2, sizeof(vertex_data), offsetof(vertex_data, TexCoords)); // TextureUV

    vertex_arr->create_buffer();
}
