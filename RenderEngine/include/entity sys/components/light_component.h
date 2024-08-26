#pragma once
#include "entity sys/component.h"
#include "gl core/core shader.h"
#include "system/core_renderable.h"

using namespace lowlevelsys;

namespace wizm {
	class light_component : public lowlevelsys::core_component {
		
		
		
		
	public:

		std::shared_ptr<core_gl_shader> shader;


		glm::vec3 m_ambient;
		glm::vec3 m_diffuse;
		glm::vec3 m_specular;
	};
}