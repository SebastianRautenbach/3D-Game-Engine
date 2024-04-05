#include "system/material.h"


namespace wizm {



	core_material::core_material()
	{
		texture_buffer diffuse_in("resources/images/missing_texture.png", eDiffuse, "resources/images/missing_texture.png");
		texture_buffer specular_in("resources/images/missing_texture.png", eSpecular, "resources/images/missing_texture.png");
		m_texture.emplace_back(diffuse_in);
		m_texture.emplace_back(specular_in);
	}
	
	void core_material::on_change_material()
	{
		m_shader->use_shader();
		m_shader->setInt("material.diffuse", 0);
		m_shader->setInt("material.specular", 1);
		
		
		//wmatdata.read_file_cntx(mat_path);
	}

	void core_material::update_material()
	{
		m_shader->setFloat("material.shininess", m_shininess);

		// loop through all the textures
		for (int i = 0; i < m_texture.size(); i++) {
			
			if (m_texture[i].type == eDiffuse) {
				glActiveTexture(GL_TEXTURE0);
				m_texture[i].texture.bind_texture();
			}
			if (m_texture[i].type == eSpecular) {
				glActiveTexture(GL_TEXTURE0 + 1);
				m_texture[i].texture.bind_texture();
			}
			
		
		}
	}

	void core_material::unbind_material()
	{
		for (int i = 0; i < m_texture.size(); i++) {
			m_texture[i].texture.unbind_texture();
		}
	}


	void core_material::set_texture(std::string texture_path, eTexture_types type)
	{

		bool does_texture_preexist = false;
		for (const auto i : m_texture) {
			if (i.path == texture_path && i.type == type)
				does_texture_preexist = true;
		}
		if(!does_texture_preexist)
		{
		
			for (auto& i : m_texture)
			{
				if (i.type == type)
					i.texture.delete_texture();
			}

			switch (type) {
				case eDiffuse:
				{
					texture_buffer temp_text(texture_path.c_str(), type, texture_path);
					m_texture[0] = temp_text;
					break;
				}

				case eSpecular:
				{
					texture_buffer temp_text(texture_path.c_str(), type, texture_path);
					m_texture[1] = temp_text;
					break;
				}
			}
		}
	}

}