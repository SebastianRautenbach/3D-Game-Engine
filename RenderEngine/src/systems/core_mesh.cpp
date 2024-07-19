#include "system/core_mesh.h"
#include <utility> // For std::move

namespace lowlevelsys {

    core_mesh::core_mesh(std::vector<vertex_data> vertices, std::vector<unsigned int> indices, std::vector<core_gl_texture> textures)
        : vertices(std::move(vertices)), indices(std::move(indices)), textures(std::move(textures)) {
        setup_mesh();
    }

    core_mesh::core_mesh(core_mesh&& other) noexcept
        : vertices(std::move(other.vertices)),
        indices(std::move(other.indices)),
        textures(std::move(other.textures)),
        vertex_arr(std::move(other.vertex_arr)) {
    }

    core_mesh& core_mesh::operator=(core_mesh&& other) noexcept {
        if (this != &other) {
            vertices = std::move(other.vertices);
            indices = std::move(other.indices);
            textures = std::move(other.textures);
            vertex_arr = std::move(other.vertex_arr);
        }
        return *this;
    }

    core_mesh::~core_mesh() {
        // No need to manually delete unique_ptr
    }

    void core_mesh::draw_mesh(core_gl_shader* shader) {
        unsigned int diffuseNr = 1;
        unsigned int specularNr = 1;
        unsigned int normalNr = 1;
        unsigned int heightNr = 1;

        vertex_arr->draw_buffer(static_cast<unsigned int>(indices.size()));

        glActiveTexture(GL_TEXTURE0);
    }

    void core_mesh::setup_mesh() {
        vertex_arr = std::make_unique<core_arr_vertex_buffer>(vertices, indices);
        vertex_arr->bind_buffer();
        vertex_arr->create_attrib_arr(0, 3, sizeof(vertex_data), 0); // pos
        vertex_arr->create_attrib_arr(1, 3, sizeof(vertex_data), offsetof(vertex_data, Normal)); // normal
        vertex_arr->create_attrib_arr(2, 2, sizeof(vertex_data), offsetof(vertex_data, TexCoords)); // TextureUV
        vertex_arr->create_buffer();
    }

}