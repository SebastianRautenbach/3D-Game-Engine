#pragma once
#include "dependencies/sqlite3.h"
#include <iostream>
#include <string>
#include <vector>


struct asset_details {

	std::string path;
	std::string id;

};


class asset_importer {

public:
	std::vector<asset_details> m_all_assets;
	
public:
	asset_importer() {
		m_all_assets.emplace_back("","");
	
	}

	void insert_asset(std::string ID, std::string location) {
	
		sql = "insert into ASSETS(ID, LOCATION) values (?,?);";

		sqlite3_stmt* stmt;
		
		rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
		if (rc != SQLITE_OK) {
			std::cout << "Failed to prepare statement: %s\n", sqlite3_errmsg(db);
			sqlite3_close(db);
			return;
		}

		sqlite3_bind_text(stmt, 1, ID.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(stmt, 1, location.c_str(), -1, SQLITE_STATIC);

		rc = sqlite3_step(stmt);
		if (rc != SQLITE_DONE) {
			std::cout << "Execution failed: %s\n", sqlite3_errmsg(db);
		}
		else {
			std::cout<< "Records inserted successfully\n";
		}

		sqlite3_finalize(stmt);
	
	}

	void import_list(const char* path) {
		rc = sqlite3_open(path, &db);
		if (rc) {
			std::cout << "cant open database";
			return;
		}
		else {
			std::cout << "open database with success";
		}


		sql = "CREATE TABLE ASSETS(ID INT PRIMARY KEY NOT NULL, LOCATION TEXT NOT NULL);";
		rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);


		if (rc != SQLITE_OK) {
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
		}
		else {
			fprintf(stdout, "Table created successfully\n");
		}
		sqlite3_close(db);

		return;
	}

	static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
		int i;
		for (i = 0; i < argc; i++) {
			printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
		}
		printf("\n");
		return 0;
	}



private:
	sqlite3* db;
	char* zErrMsg = 0;
	int rc;
	const char* sql;
	const char* check_table_sql = "SELECT name FROM sqlite_master WHERE type='table' AND name='ASSETS';";


};