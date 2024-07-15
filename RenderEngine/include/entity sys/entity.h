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
		
		void add_component(std::shared_ptr<core_component> component);
		std::shared_ptr<core_component> get_component(eCompType comp_type);
		int get_component_index(eCompType comp_type);
		void remove_component(unsigned int index);
		void set_component(unsigned int index, std::shared_ptr<core_component> component);
		
		std::shared_ptr<core_component> get_selected_comp() { return m_selected_comp; }
		void set_selected_comp(std::shared_ptr<core_component> component) { m_selected_comp = component; }


		//////////////////////////////////////////////////
		//////////  SERIALIZATION METHOD /////////////////
		//////////////////////////////////////////////////



		void save_data(std::string parent_name, std::string index) const override {

			filedata::ZER save_;
			save_.read_file_cntx();

			save_[m_ent_ID]["transform"]["position"].set_float("x", { get_position().x });
			save_[m_ent_ID]["transform"]["position"].set_float("y", { get_position().y });
			save_[m_ent_ID]["transform"]["position"].set_float("z", { get_position().z });

			save_[m_ent_ID]["transform"]["rotation"].set_float("x", { get_rotation().x });
			save_[m_ent_ID]["transform"]["rotation"].set_float("y", { get_rotation().y });
			save_[m_ent_ID]["transform"]["rotation"].set_float("z", { get_rotation().z });

			save_[m_ent_ID]["transform"]["scale"].set_float("x", { get_scale().x });
			save_[m_ent_ID]["transform"]["scale"].set_float("y", { get_scale().y });
			save_[m_ent_ID]["transform"]["scale"].set_float("z", { get_scale().z });



			save_[m_ent_ID]["tags"].set_string("tags", entity_tags->tags);
			save_.save_file(save_);

			for (int i = 0; i < m_components_list.size(); i++) {
				m_components_list[i]->save_data(m_ent_ID, std::to_string(i));
			}
		}

	public:

		std::string m_ent_ID;

		core_tag* entity_tags;
		std::vector<std::shared_ptr<core_component>> m_components_list;

	private:
		std::shared_ptr<core_component> m_selected_comp;
	};


}