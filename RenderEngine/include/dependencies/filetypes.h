#pragma once
#include <string>
#include <unordered_set>

const std::unordered_set<std::string> MESH_FILE_EXTENSIONS = { ".obj", ".fbx" };
const std::unordered_set<std::string> SOUND_FILE_EXTENSION = { ".wav", ".mp3"};
const std::unordered_set<std::string> TEXTURE_FILE_EXTENSION = { ".jpg", ".png" };
const std::unordered_set<std::string> SCRIPT_FILE_EXTENSION = { ".as", ".wizs" };
const std::unordered_set<std::string> MATERIAL_FILE_EXTENSION = { ".wmat" };
const std::unordered_set<std::string> ENTITY_FILE_EXTENSION = { ".went" };
const std::unordered_set<std::string> LEVEL_FILE_EXTENSION = { ".wlvl", ".zer"};



inline std::string get_extension(const std::string& filename) {
    size_t dot_pos = filename.find_last_of('.');
    if (dot_pos != std::string::npos) {
        return filename.substr(dot_pos);
    }
    return "";
}

/*
-------------------------------------------------------------------------               FUNCTIONS
//
*/

inline bool is_map_file(const std::string& filename) {
    std::string ext = get_extension(filename);
    return LEVEL_FILE_EXTENSION.find(ext) != LEVEL_FILE_EXTENSION.end();
}

inline bool is_mesh_file(const std::string& filename) {
    std::string ext = get_extension(filename);
    return MESH_FILE_EXTENSIONS.find(ext) != MESH_FILE_EXTENSIONS.end();
}

inline bool is_material_file(const std::string& filename) {
    std::string ext = get_extension(filename);
    return MATERIAL_FILE_EXTENSION.find(ext) != MATERIAL_FILE_EXTENSION.end();
}

inline bool is_entity_file(const std::string& filename) {
    std::string ext = get_extension(filename);
    return ENTITY_FILE_EXTENSION.find(ext) != ENTITY_FILE_EXTENSION.end();
}

inline bool is_sound_file(const std::string& filename) {
    std::string ext = get_extension(filename);
    return SOUND_FILE_EXTENSION.find(ext) != SOUND_FILE_EXTENSION.end();
}

inline bool is_texture_file(const std::string& filename) {
    std::string ext = get_extension(filename);
    return TEXTURE_FILE_EXTENSION.find(ext) != TEXTURE_FILE_EXTENSION.end();
}

inline bool is_script_file(const std::string& filename) {

    std::string ext = get_extension(filename);
    return SCRIPT_FILE_EXTENSION.find(ext) != SCRIPT_FILE_EXTENSION.end();
}