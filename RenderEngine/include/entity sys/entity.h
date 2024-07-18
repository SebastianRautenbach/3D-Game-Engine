#pragma once
#include "system/node.h"
#include <string>
#include <vector>
#include "component.h"
#include "system/tag.h"
#include <memory>
#include "components/all_components_list.h"

using namespace lowlevelsys;

namespace wizm {


	class core_entity : public core_node
	{

	public:
	
		core_entity(std::string ent_ID);
		~core_entity();
	
		
		// entity
		void remame_entity(std::string name);
		void destroy_entity();
		core_entity* get_entity() { return this; }

		void entity_preupdate();
		void entity_update();
		void entity_postupdate();

		// component
		
		std::shared_ptr<core_component> add_component(std::shared_ptr<core_component> component);
		std::shared_ptr<core_component> get_component(eCompType comp_type);
		int get_component_index(eCompType comp_type);
		void remove_component(unsigned int index);
		void set_component(unsigned int index, std::shared_ptr<core_component> component);
		
		std::shared_ptr<core_component> get_selected_comp() { return m_selected_comp; }
		void set_selected_comp(std::shared_ptr<core_component> component) { m_selected_comp = component; }


		//////////////////////////////////////////////////
		//////////  SERIALIZATION METHOD /////////////////
		//////////////////////////////////////////////////

		void read_saved_data(std::string parent_name, std::string index) override;

		void save_data(std::string parent_name, std::string index, filedata::ZER& save_t) const override;

	public:

		std::string m_ent_ID;

		core_tag* entity_tags;
		std::vector<std::shared_ptr<core_component>> m_components_list;

	private:
		std::shared_ptr<core_component> m_selected_comp;

	};


}