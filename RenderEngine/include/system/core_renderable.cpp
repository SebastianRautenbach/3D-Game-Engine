#include "core_renderable.h"

#include "system/3d_core_camera.h"

void wizm::core_renderable::update_boundingvolume(std::vector<vertex_data> vertices)
{
        for (const auto& mvertex : vertices) {
            glm::vec3 transformedPos = glm::vec3(m_camera->GetProjectionMatrix() * glm::vec4(mvertex.Position, 1.0f));
            expand_to_include(transformedPos);
        }
}
