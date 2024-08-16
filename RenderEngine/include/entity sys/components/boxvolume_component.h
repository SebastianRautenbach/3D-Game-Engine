#pragma once
#include "entity sys/component.h"
#include "gl core/core shader.h"
#include "gl core/vertex_buffer.h"

using namespace lowlevelsys;

namespace wizm {
	class boxvolume : public lowlevelsys::core_component {
	public:

		boxvolume(glm::vec3 min, glm::vec3 max);
		
		
		void component_preupdate();
		void component_update();
		void component_postupdate();
		std::shared_ptr<core_component> _copy() const;



	public:
		std::shared_ptr<core_gl_shader> m_shader;
		std::vector<glm::vec3> m_corners;
		core_arr_vertex_buffer* vertex_buffer;
		std::vector<unsigned int> indices = {
		0, 1,  1, 3,  3, 2,  2, 0,
		4, 5,  5, 7,  7, 6,  6, 4,
		0, 4,  1, 5,  2, 6,  3, 7 
		};

	};
	
}