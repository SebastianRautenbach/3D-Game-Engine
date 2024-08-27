#pragma once
#include "gl core/core shader.h"
#include "gl core/vertex_buffer.h"


namespace wizm {



	enum eBillboardType {
		eLight,
		ePartical
	};

	struct billboard_s {
		eBillboardType eBillboard;
		core_gl_texture texture;
		core_gl_shader shader;
	};

	class billboard_core {
	public:
		billboard_core(eBillboardType type, std::shared_ptr<core_gl_shader> shader);
		void draw(glm::mat4 transform);
		~billboard_core();


	private:
		std::shared_ptr<core_gl_shader> m_shader;
		std::vector<vertex_data> m_verices;
		core_arr_vertex_buffer* vertex_buffer;
		std::vector<unsigned int> m_indices = {
			0, 1, 2,
			2, 3, 0 
		};
		core_gl_texture* texture;
	};


}