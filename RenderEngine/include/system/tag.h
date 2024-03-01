#pragma once
#include <string>
#include <vector>

namespace wizm {

	class core_tag {


	public:
		void clear_tags();
		void add_tag(std::string tag);
		void remove_tag(unsigned int index);
		void set_tag(unsigned int index, std::string new_tag);

	public:
		std::vector<std::string> tags;
	};



}