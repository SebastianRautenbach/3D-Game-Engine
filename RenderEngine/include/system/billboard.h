#pragma once
#include "gl core/core shader.h"
#include "gl core/vertex_buffer.h"
#include <unordered_map>


namespace wizm {



	enum eBillboardType {
		eLightB,
		eDirLightB,
		eSpotLightB,
		eParticalB
	};

	struct billboard_s {
		eBillboardType eBillboard;
		core_gl_texture texture;
		core_gl_shader shader;
	};

	class billboard_core {
	public:
		billboard_core(std::shared_ptr<core_gl_shader> shader);
		void draw(glm::mat4 transform, eBillboardType type, glm::vec3 tint = glm::vec3(1.0));
		~billboard_core();


	private:
		std::unordered_map<eBillboardType, std::shared_ptr<core_gl_texture>> texture_atlas;
		std::shared_ptr<core_gl_shader> m_shader;
		std::vector<vertex_data> m_verices;
		core_arr_vertex_buffer* vertex_buffer;
		std::vector<unsigned int> m_indices = {
			0, 1, 2,
			2, 3, 0 
		};
	};


}