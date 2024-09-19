#pragma once
#ifndef COMPOSE_SCRIPT_H
#define COMPOSE_SCRIPT_H
#include <string>
#include <fstream>

namespace engine_scripting 
{
    inline void create_script(std::string dir, std::string name) {

        std::string file_path = dir + "/" + name;
        std::ofstream script_file(file_path);
        if (script_file.is_open()) {
            script_file << "void on_start() {\n";
            script_file << "\n";
            script_file << "}\n";
            script_file << "\n";
            script_file << "void on_update(float delta_time) {\n";
            script_file << "\n";
            script_file << "}\n";
            script_file.close();
        }
        else {
        }


    }
}
#endif