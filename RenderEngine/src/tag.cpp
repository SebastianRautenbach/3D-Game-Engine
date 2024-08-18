#include "system/tag.h"


namespace wizm {
	void core_tag::clear_tags()
	{
		tags.clear();
	}
	void core_tag::add_tag(std::string tag)
	{
		tags.emplace_back(tag);
	}
	void core_tag::remove_tag(unsigned int index)
	{
		tags.erase(tags.begin() + index);
	}
	void core_tag::set_tag(unsigned int index, std::string new_tag)
	{
		tags[index] = new_tag;
	}
}