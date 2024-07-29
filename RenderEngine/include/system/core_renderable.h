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
        wizm::core_3d_camera* m_camera;
	};
}