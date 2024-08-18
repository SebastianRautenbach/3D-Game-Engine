#include "entity sys/components/boxvolume_component.h"

wizm::boxvolume::boxvolume(glm::vec3 min, glm::vec3 max)
{

    glm::vec3 corners[8] = {
            glm::vec3(min.x, min.y, min.z),
            glm::vec3(min.x, min.y, max.z),
            glm::vec3(min.x, max.y, min.z),
            glm::vec3(min.x, max.y, max.z),
            glm::vec3(max.x, min.y, min.z),
            glm::vec3(max.x, min.y, max.z),
            glm::vec3(max.x, max.y, min.z),
            glm::vec3(max.x, max.y, max.z)
    };

    std::vector<vertex_data> vertices;

    for (const auto& corner : corners) {
        vertices.emplace_back(corner);
    }

    vertex_buffer = new core_arr_vertex_buffer(vertices, indices);

	vertex_buffer->bind_buffer();
    vertex_buffer->create_attrib_arr(0, 3, sizeof(vertex_data), 0);
	vertex_buffer->create_buffer();
}

void wizm::boxvolume::component_preupdate()
{
}

void wizm::boxvolume::component_update()
{
	m_shader->use_shader();
	
    glLineWidth(5.f);
    m_shader->setMat4("model", glm::mat4(1));
    vertex_buffer->bind_buffer();
    glDrawElements(GL_LINES, indices.size(), GL_UNSIGNED_INT, 0);
    vertex_buffer->unbind_buffer();
}

void wizm::boxvolume::component_postupdate()
{
}

std::shared_ptr<core_component> wizm::boxvolume::_copy() const
{
    return std::shared_ptr<core_component>();
}
