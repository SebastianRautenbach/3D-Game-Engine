#pragma once
#include "dependencies/sqlite3.h"
#include <iostream>
#include <string>
#include <vector>
#include "other utils/IDGEN.h"


struct asset_details {

	std::string path;
	std::string id;
    std::string type;

};


class asset_importer {
public:
    std::vector<asset_details> m_all_assets;

    asset_importer(std::string path = "assets.db") {
        initialize_db(path);
    }

    ~asset_importer() {
        sqlite3_close(db);
    }

    void remove_from_database(std::string id) {
        std::string sql = "DELETE FROM assets WHERE id ='" + id + "';";
        rc = sqlite3_exec(db, sql.c_str(), nullptr, 0, &zErrMsg);
        if (rc != SQLITE_OK) {
            std::cerr << "SQL error: " << zErrMsg << std::endl;
            sqlite3_free(zErrMsg);
        }
    }

    void add_to_database(const asset_details& asset) {
        for (auto a : retrieve_all_assets()) {
            if (asset.path == a.path)
                return;
        }
        insert_asset(asset);
    }

    void insert_asset(const asset_details& asset) {
        std::string sql = "INSERT INTO assets (id, path, type) VALUES ('" + lowlevelsys::generate_unique_id() + "', '" + asset.path + "', '" + asset.type + "');";
        rc = sqlite3_exec(db, sql.c_str(), nullptr, 0, &zErrMsg);
        if (rc != SQLITE_OK) {
            std::cerr << "SQL error: " << zErrMsg << std::endl;
            sqlite3_free(zErrMsg);
        }
    }

    std::vector<asset_details> retrieve_all_assets() {
        m_all_assets.clear();
        std::string sql = "SELECT id, path, type FROM assets;";
        rc = sqlite3_exec(db, sql.c_str(), callback, this, &zErrMsg);
        if (rc != SQLITE_OK) {
            std::cerr << "SQL error: " << zErrMsg << std::endl;
            sqlite3_free(zErrMsg);
        }
        return m_all_assets;
    }

private:
    sqlite3* db;
    char* zErrMsg = nullptr;
    int rc;

    static int callback(void* data, int argc, char** argv, char** azColName) {
        auto* importer = static_cast<asset_importer*>(data);
        asset_details asset;
        for (int i = 0; i < argc; i++) {
            std::string colName = azColName[i];
            if (colName == "id") {
                asset.id = argv[i] ? argv[i] : "";
            }
            else if (colName == "path") {
                asset.path = argv[i] ? argv[i] : "";
            }
            else if (colName == "type") {
                asset.type = argv[i] ? argv[i] : "";
            }
        }
        importer->m_all_assets.push_back(asset);
        return 0;
    }

    void initialize_db(std::string path) {
        rc = sqlite3_open(path.c_str(), &db);
        if (rc) {
            std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
            return;
        }
        else {
    
        }

        const char* sql = "CREATE TABLE IF NOT EXISTS assets ("
            "id TEXT PRIMARY KEY NOT NULL, "
            "path TEXT NOT NULL, "
            "type TEXT NOT NULL);";
        rc = sqlite3_exec(db, sql, nullptr, 0, &zErrMsg);
        if (rc != SQLITE_OK) {
            std::cerr << "SQL error: " << zErrMsg << std::endl;
            sqlite3_free(zErrMsg);
        }
        else {
         
        }
    }
};
