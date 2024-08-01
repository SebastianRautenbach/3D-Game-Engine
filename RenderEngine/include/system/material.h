#pragma once
#include "gl core/core shader.h"
#include <string>
#include <vector>
#include "system/assets/texture_asset.h"

namespace wizm {

	class core_material {
	
	public:
		core_material();
		~core_material();
		void update_material();
		void unbind_material();
		void on_change_material();

		void set_shader(unsigned int shader_index);

	public:
		std::vector< std::shared_ptr<texture_asset>> m_texture_n;

		std::string diffuse_asset_id = "";
		std::string specular_asset_id = "";

	

		// shader library
		std::vector<std::shared_ptr<core_gl_shader>> m_shader_library;

		// current shader running
		std::shared_ptr<core_gl_shader> m_shader;




		std::string mat_path;
		float m_shininess = 32.f;

	};


}