#pragma once
#include "system/assets.h"
#include <filesystem>
#include "other utils/ZER.h"

namespace wizm {

	class entity_asset : public core_asset {

	public:
		std::string _path;
		filedata::ZER data;

		void load(const std::string& path) override {

			data.read_file_cntx(path);

			_path = path;
			std::filesystem::path file_path(path);
			file_name = file_path.filename().string();
		}
	};

}