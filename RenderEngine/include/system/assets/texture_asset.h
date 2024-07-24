#pragma once
#include "system/assets.h"
#include "gl core/core shader.h"

namespace wizm {


	class texture_asset : public core_asset {

	public:
		~texture_asset() {
			texture->delete_texture();
			delete texture;
		}

		void load(const std::string& path) override {
			if(path.find("png") != -1)
				texture = new core_gl_texture(path.c_str(),true, GL_RGBA);
			else
				texture = new core_gl_texture(path.c_str(),true, GL_RGB);
		}

		void unbind() {
			texture->unbind_texture();
		}

		void draw(core_gl_shader* shader) {
			texture->bind_texture();
		}

		core_gl_texture* texture;
	};
}
