#pragma once
#include "component_types.h"
#include <glm/glm.hpp>
#include "system/node.h"
#include "system/tag.h"
#include "gl core/core shader.h"

using namespace wizm;

namespace lowlevelsys {


	class core_component : public core_node
	{
		
	public:

		virtual void component_preupdate() = 0;
		virtual void component_update() = 0;
		virtual void component_postupdate() = 0;

		// default component shit

		void remove_component();


	public:

		eCompType m_component_type;

		bool m_is_active;
		bool m_is_visible;

		wizm::core_tag* component_tags;
	};
}