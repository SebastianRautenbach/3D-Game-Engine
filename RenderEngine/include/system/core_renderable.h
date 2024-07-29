#pragma once
#include "bounding_volume.h"
#include <vector>
#include <memory>
#include "gl core/vertex_buffer.h"

namespace wizm {

	class core_3d_camera;

	class core_renderable : public bounding_volume {

    public:
        void update_boundingvolume(std::vector<vertex_data> vertices);
        

    public:
        std::unique_ptr<wizm::core_3d_camera> m_camera;
        
        //void updateBoundingBox() {
        //    for (const auto& vertex : vertices) {
        //        glm::vec3 transformedPos = glm::vec3(modelMatrix * glm::vec4(vertex.position, 1.0f));
        //        boundingBox.expandToInclude(transformedPos);
        //    }
        //}


	};
}