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
		void render_model(core_gl_shader* shader);


	public:
		std::vector<core_gl_texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
		std::vector<core_mesh>    meshes;
		std::string directory;
		bool gammaCorrection;

	private:

		void loadModel(std::string path);
		void processNode(aiNode* node, const aiScene* scene);
		core_mesh processMesh(aiMesh* mesh, const aiScene* scene);
		std::vector<core_gl_texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
			std::string typeName);
	};
}