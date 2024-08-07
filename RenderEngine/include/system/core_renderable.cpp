#include "core_renderable.h"
#include "system/3d_core_camera.h"
#include <array>


void wizm::core_renderable::init_boundingvolume(std::vector<vertex_data> vertices, const glm::mat4& model_mtx)
{        
    //for (const auto& mvertex : vertices) {
    //    glm::vec3 transformed_pos = glm::vec3(model_mtx * glm::vec4(mvertex.Position, 1.0f));
    //    this->expand_to_include(transformed_pos);
    //}


    for (const auto& vertex_data : vertices) {
        auto& vertex = vertex_data.Position;
        if (vertex.x < min_point.x) min_point.x = vertex.x;
        if (vertex.y < min_point.y) min_point.y = vertex.y;
        if (vertex.z < min_point.z) min_point.z = vertex.z;

        if (vertex.x > max_point.x) max_point.x = vertex.x;
        if (vertex.y > max_point.y) max_point.y = vertex.y;
        if (vertex.z > max_point.z) max_point.z = vertex.z;
    }

}

void wizm::core_renderable::update_boundingvolume(const glm::vec3& world_pos, const glm::vec3& world_rot, const glm::vec3& world_scale)
{

    glm::mat4 translation_mtx = glm::translate(glm::mat4(1.0f), world_pos);
    glm::quat rotation_quat = glm::quat(glm::vec3(world_rot.x, world_rot.y, world_rot.z));
    glm::mat4 rotation_mtx = glm::mat4(rotation_quat);
    glm::mat4 scale_mtx = glm::scale(glm::mat4(1.0f), world_scale);
    glm::mat4 model_mtx = translation_mtx * rotation_mtx * scale_mtx;


    std::array<glm::vec3, 8> bounding_box_corners = {
        min_point,
        glm::vec3(min_point.x, min_point.y, max_point.z),
        glm::vec3(min_point.x, max_point.y, min_point.z),
        glm::vec3(min_point.x, max_point.y, max_point.z),
        glm::vec3(max_point.x, min_point.y, min_point.z),
        glm::vec3(max_point.x, min_point.y, max_point.z),
        glm::vec3(max_point.x, max_point.y, min_point.z),
        max_point
    };
    

    for (const auto& corner : bounding_box_corners) {
        glm::vec3 transformed_corner = glm::vec3(model_mtx * glm::vec4(corner, 1.0f));
        this->expand_to_include(transformed_corner);

    }
}
