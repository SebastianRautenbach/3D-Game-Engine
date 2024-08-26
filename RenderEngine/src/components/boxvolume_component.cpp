#include "entity sys/components/boxvolume_component.h"

wizm::boxvolume::boxvolume(const glm::vec3& center, const glm::vec3& extents, const glm::vec3 axes[3])
{

    glm::vec3 corners[8];
    glm::vec3 axis0 = axes[0] * extents.x;
    glm::vec3 axis1 = axes[1] * extents.y;
    glm::vec3 axis2 = axes[2] * extents.z;

    corners[0] = center - axis0 - axis1 - axis2;
    corners[1] = center - axis0 - axis1 + axis2;
    corners[2] = center - axis0 + axis1 - axis2;
    corners[3] = center - axis0 + axis1 + axis2;
    corners[4] = center + axis0 - axis1 - axis2;
    corners[5] = center + axis0 - axis1 + axis2;
    corners[6] = center + axis0 + axis1 - axis2;
    corners[7] = center + axis0 + axis1 + axis2;

    
    std::vector<vertex_data> vertices;
    for (const auto& corner : corners) {
        vertices.emplace_back(corner);
    }


    vertex_buffer = new core_arr_vertex_buffer(vertices, indices);
    vertex_buffer->bind_buffer();
    vertex_buffer->create_attrib_arr(0, 3, sizeof(vertex_data), 0);
    vertex_buffer->create_buffer();
}

wizm::boxvolume::~boxvolume()
{
    delete vertex_buffer;
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
