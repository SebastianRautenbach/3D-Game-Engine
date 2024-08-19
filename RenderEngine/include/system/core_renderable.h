#pragma once
#include "bounding_volume.h"
#include <vector>
#include <memory>
#include "gl core/vertex_buffer.h"

namespace wizm {

	class core_3d_camera;

	class core_renderable : public bounding_volume {

    public:
        core_renderable() = default;
        
        void init_boundingvolume(std::vector<vertex_data> vertices);
        void update_boundingvolume(const glm::vec3& world_pos, const glm::vec3& world_rot, const glm::vec3& world_scale);
        void update_boundingvolume(const glm::mat4& model_matrix);
     
    public:
        bool has_boundvolume = false;
        std::shared_ptr<wizm::core_3d_camera> m_camera = nullptr;
	};
}