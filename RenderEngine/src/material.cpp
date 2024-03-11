#include "system/material.h"


namespace wizm {



	core_material::core_material(std::string albedo_path, std::string specular_path)
	{
		m_albedo_texture = new core_gl_texture(albedo_path.c_str());
		m_specular_texture = new core_gl_texture(specular_path.c_str());
	}

	void core_material::on_change_material()
	{
		m_shader->use_shader();
		m_shader->setInt("material.diffuse", 0);
		m_shader->setInt("material.specular", 1);
	}

	void core_material::update_material()
	{
		m_shader->use_shader();


		glActiveTexture(GL_TEXTURE0);
		m_albedo_texture->bind_texture();

		glActiveTexture(GL_TEXTURE1);
		m_specular_texture->bind_texture();
	}

	void core_material::unbind_material()
	{
		m_albedo_texture->unbind_texture();
		m_specular_texture->unbind_texture();
	}

	void core_material::set_texture(std::string texture_path, eMaterial_types type)
	{
		switch (type)
		{
		case mDiffuse:
			m_albedo_texture->set_texture(texture_path.c_str());
			break;

		case mSpecular:
			m_specular_texture->set_texture(texture_path.c_str());
			break;
		}
	}

}