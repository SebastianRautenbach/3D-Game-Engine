#pragma once
#include "dependencies/sqlite3.h"
#include <iostream>
#include <string>
#include <vector>


struct asset_details {

	std::string path;
	std::string id;
    std::string type;

};


class asset_importer {
public:
    std::vector<asset_details> m_all_assets;

    asset_importer() {
        initialize_db();
    }

    ~asset_importer() {
        sqlite3_close(db);
    }

    void insert_asset(const asset_details& asset) {
        std::string sql = "INSERT INTO assets (id, path, type) VALUES ('" + asset.id + "', '" + asset.path + "', '" + asset.type + "');";
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

    void initialize_db() {
        rc = sqlite3_open("assets.db", &db);
        if (rc) {
            std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
            return;
        }
        else {
            std::cout << "Opened database successfully" << std::endl;
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
            std::cout << "Table created successfully" << std::endl;
        }
    }
};
