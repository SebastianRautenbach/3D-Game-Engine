#pragma once
#include "gl core/core shader.h"
#include <string>

namespace wizm {

	class core_material {
	
	public:
		core_material(/*core_gl_shader* shader,*/ std::string albedo_path);
		void update_material();
		void unbind_material();

	public:
		core_gl_texture* m_albedo_texture;
		core_gl_shader* m_shader;

	};


}