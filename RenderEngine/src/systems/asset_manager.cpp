#include "system/asset_manager.h"
#include "other utils/IDGEN.h"

wizm::asset_manager::asset_manager(std::string location)
{
    if (sqlite3_open(location.c_str(), &database) != SQLITE_OK)
    {
        std::filesystem::path currentPath = std::filesystem::current_path();
        location = currentPath.string();
        location += "\\asset info";

        if (!std::filesystem::exists(location)) {
            if (!std::filesystem::create_directories(location)) {
                std::cerr << "Error creating directory!" << std::endl;
            }
        }

        location += "\\info.db";

        std::ofstream file(location.c_str());
        if (!file.is_open()) {
            std::cerr << "Error opening file!" << std::endl; // Return with error
        }
        file.close();

        sqlite3_open(location.c_str(), &database);
    }

    const char* sqlCreateTable =
        "CREATE TABLE IF NOT EXISTS Assets("
        "ID INT UNSIGNED PRIMARY KEY, "
        "Type INT, "
        "Location TEXT UNIQUE);";
    char* errorMessage = nullptr;
    if (sqlite3_exec(database, sqlCreateTable, nullptr, nullptr, &errorMessage) != SQLITE_OK) {
        std::cerr << "SQL error: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
    }

}

void wizm::asset_manager::add_asset(eAssetType type, std::string location)
{
    std::string sqlInsert = "INSERT OR IGNORE INTO Assets(ID, Type, Location) VALUES (?, ?, ?);";
    sqlite3_stmt* statement;
    if (sqlite3_prepare_v2(database, sqlInsert.c_str(), -1, &statement, nullptr) == SQLITE_OK) {
        
        sqlite3_bind_int(statement, 1, lowlevelsys::generate_unique_id());
        sqlite3_bind_int(statement, 2, static_cast<int>(type));
        sqlite3_bind_text(statement, 3, location.c_str(), -1, SQLITE_TRANSIENT);

        if (sqlite3_step(statement) != SQLITE_DONE) {
            std::cerr << "Error inserting asset: " << sqlite3_errmsg(database) << std::endl;
        }
        sqlite3_finalize(statement);
    }

}

int wizm::asset_manager::get_asset_id(eAssetType type, std::string location)
{
    std::string sqlSelect = "SELECT ID FROM Assets WHERE Type = ? AND Location = ? LIMIT 1;";
    sqlite3_stmt* statement;
    if (sqlite3_prepare_v2(database, sqlSelect.c_str(), -1, &statement, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(statement, 1, static_cast<int>(type));
        sqlite3_bind_text(statement, 2, location.c_str(), -1, SQLITE_TRANSIENT);

        if (sqlite3_step(statement) == SQLITE_ROW) {
            int id = sqlite3_column_int(statement, 0);
            sqlite3_finalize(statement);
            return id;
        }
        sqlite3_finalize(statement);
    }
    return -1; // not found or error

}

std::string wizm::asset_manager::get_asset_path(int asset_id)
{
    std::stringstream query;
    query << "SELECT Location FROM Assets WHERE ID = " << asset_id << ";";

    // Execute the query
    sqlite3_stmt* statement;
    if (sqlite3_prepare_v2(database, query.str().c_str(), -1, &statement, nullptr) == SQLITE_OK) {
        if (sqlite3_step(statement) == SQLITE_ROW) {
            const unsigned char* path = sqlite3_column_text(statement, 0);
            std::string assetPath(reinterpret_cast<const char*>(path));
            sqlite3_finalize(statement);
            return assetPath;
        }
        else {
            sqlite3_finalize(statement);
            std::cerr << "No asset found with ID: " << asset_id << std::endl;
          
        }
    }
    else {
        std::cerr << "SQL error: " << sqlite3_errmsg(database) << std::endl;
       
    }

    return "";
}

eAssetType wizm::asset_manager::get_asset_type(int asset_id)
{
    std::stringstream query;
    query << "SELECT Type FROM Assets WHERE ID = " << asset_id << ";";

    // Execute the query
    sqlite3_stmt* statement;
    if (sqlite3_prepare_v2(database, query.str().c_str(), -1, &statement, nullptr) == SQLITE_OK) {
        if (sqlite3_step(statement) == SQLITE_ROW) {
            int type = sqlite3_column_int(statement, 0);
            sqlite3_finalize(statement);
            return static_cast<eAssetType>(type);
        }
        else {
            sqlite3_finalize(statement);
            std::cerr << "No asset found with ID: " << asset_id << std::endl;
            // You might want to handle this case differently (throw exception, return default type, etc.)
        }
    }
    else {
        std::cerr << "SQL error: " << sqlite3_errmsg(database) << std::endl;
        // Handle error (return default type or throw exception)
    }

    return static_cast<eAssetType>(-1);
}
