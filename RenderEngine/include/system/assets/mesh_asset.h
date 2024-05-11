#pragma once
#include "system/assets.h"
#include "system/core_model.h"


using namespace lowlevelsys;


namespace wizm {

	class staticmesh_asset : public core_asset {
	public:
		void load(const std::string& path) override {
			m_model = new core_model(path.c_str());
		}
		void draw(core_gl_shader* shader) {
			m_model->render_model(shader);
		}
		core_model* m_model;
	};

}