#pragma once
#include "entity sys/component.h"
#include "gl core/core shader.h"
#include "system/core_renderable.h"

using namespace lowlevelsys;

namespace wizm {
	class light_component : public lowlevelsys::core_component, public core_renderable {

	public:
		
		light_component(glm::vec3 ambient = glm::vec3(0.05f, 0.05f, 0.05f),
			glm::vec3 diffuse = glm::vec3(0.8f, 0.8f, 0.8f),
			glm::vec3 specular = glm::vec3(1.0f, 1.0f, 1.0f));


		virtual std::shared_ptr<core_component> _copy() const = 0;

		
	public:

		std::shared_ptr<core_gl_shader> shader;


		glm::vec3 m_ambient;
		glm::vec3 m_diffuse;
		glm::vec3 m_specular;
	};
}