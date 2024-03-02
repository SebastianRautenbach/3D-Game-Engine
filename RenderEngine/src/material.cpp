#include "system/material.h"


namespace wizm {



	core_material::core_material(/*core_gl_shader* shader, */std::string albedo_path)
	{
		m_albedo_texture = new core_gl_texture(albedo_path.c_str());
	}

	void core_material::update_material()
	{
		m_shader->use_shader();
		m_albedo_texture->bind_texture();
	}

	void core_material::unbind_material()
	{
		m_albedo_texture->unbind_texture();
	}

	void core_material::set_texture(std::string albedo_path)
	{
		m_albedo_texture->set_texture(albedo_path.c_str());
	}

}