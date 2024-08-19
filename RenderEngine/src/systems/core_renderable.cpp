#include "system/core_renderable.h"
#include "system/3d_core_camera.h"
#include <array>
#include <iostream>


void wizm::core_renderable::init_boundingvolume(std::vector<vertex_data> vertices)
{          
    this->has_boundvolume = true;
    for (const auto& vertex : vertices) {
        min_point_local.x = std::min(min_point_local.x, vertex.Position.x);
        min_point_local.y = std::min(min_point_local.y, vertex.Position.y);
        min_point_local.z = std::min(min_point_local.z, vertex.Position.z);

        max_point_local.x = std::max(max_point_local.x, vertex.Position.x);
        max_point_local.y = std::max(max_point_local.y, vertex.Position.y);
        max_point_local.z = std::max(max_point_local.z, vertex.Position.z);
    }
}

void wizm::core_renderable::update_boundingvolume(const glm::vec3& world_pos, const glm::vec3& world_rot, const glm::vec3& world_scale)
{
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(transform, world_pos);
    transform = glm::rotate(transform, glm::radians(world_rot.z), glm::vec3(0, 0, 1));
    transform = glm::rotate(transform, glm::radians(world_rot.y), glm::vec3(0, 1, 0));
    transform = glm::rotate(transform, glm::radians(world_rot.x), glm::vec3(1, 0, 0));
    transform = glm::scale(transform, world_scale);

    glm::vec3 corners[8] = {
            glm::vec3(min_point_local.x, min_point_local.y, min_point_local.z),
            glm::vec3(min_point_local.x, min_point_local.y, max_point_local.z),
            glm::vec3(min_point_local.x, max_point_local.y, min_point_local.z),
            glm::vec3(min_point_local.x, max_point_local.y, max_point_local.z),
            glm::vec3(max_point_local.x, min_point_local.y, min_point_local.z),
            glm::vec3(max_point_local.x, min_point_local.y, max_point_local.z),
            glm::vec3(max_point_local.x, max_point_local.y, min_point_local.z),
            glm::vec3(max_point_local.x, max_point_local.y, max_point_local.z)
    };

    
    min_point = glm::vec3(std::numeric_limits<float>::max());
    max_point = glm::vec3(std::numeric_limits<float>::lowest());


    for (const auto& corner : corners) {
        glm::vec3 trans_corner = glm::vec3(transform * glm::vec4(corner, 1.0f));
        min_point.x = std::min(min_point.x, trans_corner.x);
        min_point.y = std::min(min_point.y, trans_corner.y);
        min_point.z = std::min(min_point.z, trans_corner.z);

        max_point.x = std::max(max_point.x, trans_corner.x);
        max_point.y = std::max(max_point.y, trans_corner.y);
        max_point.z = std::max(max_point.z, trans_corner.z);
    }



}

void wizm::core_renderable::update_boundingvolume(const glm::mat4& model_matrix)
{
    glm::mat4 transform = model_matrix;

    glm::vec3 corners[8] = {
        glm::vec3(min_point_local.x, min_point_local.y, min_point_local.z),
        glm::vec3(min_point_local.x, min_point_local.y, max_point_local.z),
        glm::vec3(min_point_local.x, max_point_local.y, min_point_local.z),
        glm::vec3(min_point_local.x, max_point_local.y, max_point_local.z),
        glm::vec3(max_point_local.x, min_point_local.y, min_point_local.z),
        glm::vec3(max_point_local.x, min_point_local.y, max_point_local.z),
        glm::vec3(max_point_local.x, max_point_local.y, min_point_local.z),
        glm::vec3(max_point_local.x, max_point_local.y, max_point_local.z)
    };

    min_point = glm::vec3(std::numeric_limits<float>::max());
    max_point = glm::vec3(std::numeric_limits<float>::lowest());

   
    for (const auto& corner : corners) {
        glm::vec3 trans_corner = glm::vec3(transform * glm::vec4(corner, 1.0f));
        min_point.x = std::min(min_point.x, trans_corner.x);
        min_point.y = std::min(min_point.y, trans_corner.y);
        min_point.z = std::min(min_point.z, trans_corner.z);

        max_point.x = std::max(max_point.x, trans_corner.x);
        max_point.y = std::max(max_point.y, trans_corner.y);
        max_point.z = std::max(max_point.z, trans_corner.z);
    }

}

