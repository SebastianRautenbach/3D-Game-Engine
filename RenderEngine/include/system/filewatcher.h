#pragma once
#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include "system/asset_importer.h"
#include "system/assets/assettypes.h"
#include "filetypes.h"

class filewatcher {
public:
    filewatcher() {
        refresh();
    }

    void refresh() {

        asset_importer ai;
        auto paths = get_files_in_dir("GAME/Content/Assets");

        /*
            Remove all non existing files from the database
        */

        for (auto f : ai.retrieve_all_assets()) {
            if (!std::filesystem::exists(f.path))
                ai.remove_from_database(f.id);
        }

        


        for (auto p : paths)
        {
            auto e = get_extension(p);

            if (is_mesh_file(e))
            {
                ai.add_to_database(asset_details(p, "", tMESH));
                continue;
            }

            if (is_sound_file(e))
            {
                ai.add_to_database(asset_details(p, "", tSOUND));
                continue;
            }

            if (is_texture_file(e))
            {
                ai.add_to_database(asset_details(p, "", tTEXTURE));
                continue;
            }

            if (is_script_file(e))
            {
                ai.add_to_database(asset_details(p, "", tSCRIPT));
                continue;
            }

            if (is_material_file(e))
            {
                ai.add_to_database(asset_details(p, "", tMATERIAL));
                continue;
            }
        }
    }

private:



    std::vector<std::string> get_files_in_dir(const std::string& directoryPath) {
        std::vector<std::string> files;
        try {
            for (const auto& entry : std::filesystem::recursive_directory_iterator(directoryPath)) {
                if (entry.is_regular_file()) {
                    files.push_back(entry.path().string());
                }
            }
        }
        catch (const std::filesystem::filesystem_error& e) {
            std::cerr << "Filesystem error: " << e.what() << std::endl;
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
        return files;
    }


};