#include "system/material.h"


namespace wizm {



	core_material::core_material()
	{
	}

	core_material::~core_material()
	{
	}
	
	void core_material::on_change_material()
	{
		m_shader->use_shader();
		m_shader->setInt("material.diffuse", 0);
		m_shader->setInt("material.specular", 1);
	}

	void core_material::update_material()
	{
		m_shader->setFloat("material.shininess", m_shininess);

		if(!diffuse_asset_id.empty())
		{
			glActiveTexture(GL_TEXTURE0);
			m_texture_n[0]->draw(nullptr);
		}

		if(!specular_asset_id.empty())
		{
			glActiveTexture(GL_TEXTURE0 + 1);
			m_texture_n[1]->draw(nullptr);
		}

	}

	void core_material::unbind_material()
	{
		for (int i = 0; i < m_texture_n.size(); i++) {
			m_texture_n[i]->unbind();
		}
	}



}