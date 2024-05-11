#pragma once
#include <string>



namespace wizm {


	class core_asset {
	public:
		virtual ~core_asset() = default;
		virtual void load(const std::string& path) = 0;
	};


}