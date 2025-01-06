#pragma once
#ifndef COMPOSE_MATERIAL_H
#define COMPOSE_MATERIAL_H
#include <string>
#include <fstream>

namespace wizm
{
	inline void create_material(std::string dir, std::string name) {
        std::string file_path = dir + "/" + name;
        std::ofstream level_file(file_path);
        if (level_file.is_open()) {


            level_file << "material{\n";
            level_file << "textures{\n";
            level_file << "diffuse:;\n";
            level_file << "specular:;\n";
            level_file << "}\n";
            level_file << "shininess:32.000000;\n";
            level_file << "}\n";
            level_file << "}\n";



            level_file.close();
        }
        else {
        }
	}
}

#endif