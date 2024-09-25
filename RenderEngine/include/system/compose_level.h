#pragma once
#ifndef COMPOSE_LEVEL_H
#define COMPOSE_LEVEL_H
#include <string>
#include <fstream>

namespace wizm
{
    inline void create_level(std::string dir, std::string name) {

        std::string file_path = dir + "/" + name;
        std::ofstream level_file(file_path);
        if (level_file.is_open()) {
            
            /* Add some sun u know
			*/
            
		level_file <<	"directionallight{\n";
		level_file <<		"directionallight0{\n";
		level_file <<				"light{\n";
		level_file <<					"m_ambient:0.119048,0.119046,0.119046;\n";
		level_file <<					"m_diffuse:0.400000,0.400000,0.400000;\n";
		level_file <<					"m_specular:0.500000,0.500000,0.500000;\n";
		level_file <<					"m_brightness:1.0;\n";
		level_file <<				"}\n";
		level_file <<				"transform{\n";
		level_file <<					"position:0.000000,0.000000,0.000000;\n";
		level_file <<					"rotation:0.000000,0.000000,0.000000;\n";
		level_file <<					"scale:1.000000,1.000000,1.000000;\n";
		level_file <<				"}\n";
		level_file <<			"}\n";
		level_file <<			"tags{\n";
		level_file <<			"}\n";
		level_file <<			"transform{\n";
		level_file <<				"position:0.000000,0.000000,0.000000;\n";
		level_file <<				"rotation:0.000000,0.000000,0.000000;\n";
		level_file <<				"scale:1.000000,1.000000,1.000000;\n";
		level_file <<			"}\n";
		level_file <<	"}\n";
            
            
            
            level_file.close();
        }
        else {
        }


    }
}
#endif