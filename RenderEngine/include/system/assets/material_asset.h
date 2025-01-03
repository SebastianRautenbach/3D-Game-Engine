#pragma once
#include "system/assets.h"
#include "texture_asset.h"
#include <filesystem>
#include "other utils/ZER.h"
#include "gl core/core shader.h"

namespace wizm {

	class material_asset : public core_asset {
		
	public:
		
		void load(const std::string& path) override {
			filedata::ZER save_object;
			save_object.read_file_cntx(path);
			diffuse_asset_id = save_object["material"]["textures"].get_string("diffuse")[0];
			specular_asset_id = save_object["material"]["textures"].get_string("specular")[0];
			m_shininess = save_object["material"].get_float("shininess")[0];
		}

		void unbind() {
			if (m_diffuse_texture) {
				m_diffuse_texture->unbind();
			}
			if (m_specular_texture) {
				m_specular_texture->unbind();
			}
		}

		void draw(std::shared_ptr<core_gl_shader> m_shader) {
			
			m_shader->setFloat("material.shininess", m_shininess);			
			m_shader->setInt("material.diffuse", 0);
			m_shader->setInt("material.specular", 1);
			
			if (m_diffuse_texture) {
				glActiveTexture(GL_TEXTURE0);
				m_diffuse_texture->draw(nullptr);
			}
			if (m_specular_texture) {
				glActiveTexture(GL_TEXTURE1);
				m_specular_texture->draw(nullptr);
			}
		}
		
		std::string diffuse_asset_id = "";
		std::string specular_asset_id = "";
		
		std::shared_ptr<texture_asset> m_diffuse_texture;
		std::shared_ptr<texture_asset> m_specular_texture;

		float m_shininess = 32.f;
	};

}