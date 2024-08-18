#include "system/material.h"


namespace wizm {



	core_material::core_material()
	{
		m_texture_n.emplace_back();
		m_texture_n.emplace_back();
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

	void core_material::update_material(glm::mat4 model)
	{
		m_shader->use_shader();

		m_shader->setFloat("material.shininess", m_shininess);
		m_shader->setInt("code", select_model_id);

		if (m_texture_n[0])
		{
			glActiveTexture(GL_TEXTURE0);
			m_texture_n[0]->draw(nullptr);
		}

		if (m_texture_n[1])
		{
			glActiveTexture(GL_TEXTURE0 + 1);
			m_texture_n[1]->draw(nullptr);
		}


		m_shader->setMat4("model", model);

	}

	void core_material::unbind_material()
	{
		for (int i = 0; i < m_texture_n.size(); i++) {
			if (m_texture_n[i])
				m_texture_n[i]->unbind();
		}
	}

	void core_material::set_shader(unsigned int shader_index)
	{
		if(m_shader_library.size() - 1 >= shader_index)
			m_shader = m_shader_library[shader_index];
		on_change_material();
	}



}