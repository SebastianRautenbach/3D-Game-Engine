#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <iterator>
#include <fstream>

//////////////////////////////////////////////////////////////////////////
// File to string
//////////////////////////////////////////////////////////////////////////

inline std::string read_file_to_str(const char* path) {

	std::ifstream path_src(path, std::ios::binary);



	std::vector<char> out((std::istreambuf_iterator<char>(path_src)),
		std::istreambuf_iterator<char>());
	out.emplace_back('\0');

	path_src.close();

	return out.data();
}

