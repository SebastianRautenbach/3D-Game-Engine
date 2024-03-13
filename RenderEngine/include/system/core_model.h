#pragma once
#include "gl core/core shader.h"
#include "core_mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace lowlevelsys {
	class core_model {
	public:
		core_model(const char* file_path);
		void render_model();
	};
}