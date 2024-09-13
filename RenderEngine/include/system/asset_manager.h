#pragma once
#include <string>
#include <vector>
#include "sqlite3.h"
#include "assettypes.h"
#include <iostream>
#include <sstream>
#include <filesystem>
#include <fstream>
#include <unordered_map>
#include "system/assets.h"
#include "asset_importer.h"
#include "system/assets/assettypes.h"



namespace wizm {

	class asset_manager {
    private:
        std::unordered_map<std::string, std::shared_ptr<core_asset>> m_assets;

    public:
        asset_manager();


    public:

        asset_details get_asset_details_from_id(std::string ID) {
            auto assets = asset_import.retrieve_all_assets();
            for (const auto& asset : assets) {
                if (asset.id == ID)
                    return asset;
            }
            return asset_details("", "", "");
        }

        void assign_assets();

        void load_assets_db();

        template <typename T>
        std::shared_ptr<T> load(const std::string& asset_id, const std::string& path) {
            auto it = m_assets.find(asset_id);
            if (it != m_assets.end()) {
                return std::dynamic_pointer_cast<T>(it->second);
            }

            std::shared_ptr<T> asset = std::make_shared<T>();
            asset->load(path);
            m_assets[asset_id] = asset;
            return asset;
        }

    private:
        unsigned int total_entities = 0;
        asset_importer asset_import;

	};
}