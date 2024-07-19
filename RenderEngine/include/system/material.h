#pragma once
#include "gl core/core shader.h"
#include "material_types.h"
#include <string>
#include <vector>

namespace wizm {

	struct texture_buffer {
		core_gl_texture texture;
		eTexture_types type;
		std::string path;
	};

	class core_material {
	
	public:
		core_material();
		~core_material();
		void update_material();
		void unbind_material();
		void set_texture(std::string texture_path, eTexture_types type);
		void on_change_material();

	public:
		std::vector<texture_buffer> m_texture;
		core_gl_shader* m_shader;
		std::string mat_path;
		float m_shininess = 32.f;
	};


}