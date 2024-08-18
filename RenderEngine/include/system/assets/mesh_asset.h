#pragma once
#include "system/assets.h"
#include "system/core_model.h"

using namespace lowlevelsys;


namespace wizm {

	class staticmesh_asset : public core_asset {
	public:
		void load(const std::string& path) override {
			if(!path.empty())
				m_model = new core_model(path.c_str());
		}
		void draw() {
			m_model->render_model();
		}

		unsigned int get_triangles() {
			return m_model->total_triangles;
		}


		std::vector<vertex_data> retrieve_all_vertices() {
			std::vector<vertex_data> vertices;
			if(this)
			for (const auto& mesh : m_model->meshes) {
				for (const auto& i : mesh.vertices) {
					vertices.emplace_back();
				}
			}
			return vertices;
		}

	private:
		core_model* m_model = NULL;
	};

}