#pragma once
#include "gl core/core shader.h"
#include "material_types.h"
#include <string>

namespace wizm {

	class core_material {
	
	public:
		core_material(std::string albedo_path, std::string specular_path);
		void update_material();
		void unbind_material();
		void set_texture(std::string texture_path, eMaterial_types type);
		void on_change_material();

	public:
		core_gl_texture* m_albedo_texture;
		core_gl_texture* m_specular_texture;
		core_gl_shader* m_shader;

	};


}