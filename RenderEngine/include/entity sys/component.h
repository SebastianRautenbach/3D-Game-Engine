#pragma once
#include "component_types.h"
#include <glm/glm.hpp>
#include "system/node.h"
#include "system/tag.h"
#include "gl core/core shader.h"
#include <memory>

using namespace wizm;

namespace lowlevelsys {


	class core_component : public core_node
	{
		
	public:

		virtual void component_preupdate() = 0;
		virtual void component_update() = 0;
		virtual void component_postupdate() = 0;
		

		void remove_component();


		void save_data(std::string parent_name) const override {
			
			filedata::ZER save_;
			save_.read_file_cntx();

			save_[parent_name][std::to_string(m_component_type)].set_float("x", { get_position().x });
			save_[parent_name][std::to_string(m_component_type)].set_float("y", { get_position().y });
			save_[parent_name][std::to_string(m_component_type)].set_float("z", { get_position().z });
			
			
			save_.save_file(save_);


		}


	public:

		eCompType m_component_type;

		bool m_is_active;
		bool m_is_visible;

		wizm::core_tag* component_tags;
	};
}