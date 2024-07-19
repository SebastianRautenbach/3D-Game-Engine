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
		
		core_component();
		~core_component();

		void remove_component();

		


	public:

		eCompType m_component_type;

		bool m_is_active;
		bool m_is_visible;

		wizm::core_tag* component_tags;
	};
}