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

    //for (unsigned int i = 0; i < textures.size(); i++)
    //{
    //    glActiveTexture(GL_TEXTURE0 + i); 
    //
    //    std::string number;
    //    std::string name = textures[i].type;
    //    if (name == "texture_diffuse")
    //        number = std::to_string(diffuseNr++);
    //    else if (name == "texture_specular")
    //        number = std::to_string(specularNr++); // transfer unsigned int to string
    //    else if (name == "texture_normal")
    //        number = std::to_string(normalNr++); // transfer unsigned int to string
    //    else if (name == "texture_height")
    //        number = std::to_string(heightNr++); // transfer unsigned int to string
    //
    //    // now set the sampler to the correct texture unit
    //    glUniform1i(glGetUniformLocation(shader->get_shader_id(), (name + number).c_str()), i);
    //    // and finally bind the texture
    //    glBindTexture(GL_TEXTURE_2D, textures[i].texture_id);
    //}
    

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
