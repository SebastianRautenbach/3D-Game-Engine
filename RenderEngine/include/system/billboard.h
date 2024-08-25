#pragma once
#include "gl core/core shader.h"
#include <string>
#include <vector>

namespace wizm {

	class core_3d_camera;

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
		billboard_core(eBillboardType type, std::shared_ptr<core_gl_shader> shader, std::shared_ptr<core_3d_camera> camera);
		void draw();


	private:
		std::shared_ptr<core_3d_camera> m_camera;
		std::shared_ptr<core_gl_shader> m_shader;
	};


}