#pragma once
#include <string>
#include <vector>
#include "sqlite3.h"
#include "assettypes.h"
#include <iostream>
#include <sstream>
#include <filesystem>
#include <fstream> 

namespace wizm {

	class asset_manager {
	public:
		asset_manager(std::string location);
		void add_asset(eAssetType type, std::string location);
		int get_asset_id(eAssetType type, std::string location);
		std::string get_asset_path(int asset_id);
		eAssetType get_asset_type(int asset_id);

	private:
		sqlite3* database;

	};


}