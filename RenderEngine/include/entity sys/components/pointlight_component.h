#pragma once
#include "entity sys/component.h"
#include "gl core/core shader.h"

namespace wizm {
	class pointlight_component : public lowlevelsys::core_component {
    public:
        pointlight_component(
            float constant = 1.0f,
            float linear = 0.09f,
            float quadratic = 0.032f,
            float radius = 3.f,
            glm::vec3 ambient = glm::vec3(0.05f, 0.05f, 0.05f), 
            glm::vec3 diffuse = glm::vec3(0.8f, 0.8f, 0.8f),
            glm::vec3 specular = glm::vec3(1.0f, 1.0f, 1.0f)
        );

        ~pointlight_component();
	    

        void component_preupdate();
        void component_update();
        void component_postupdate();
    
    public:

        unsigned int light_index = 0;
        core_gl_shader* shader;

        float m_constant;
        float m_linear;
        float m_quadratic;
        float m_radius;

        glm::vec3 m_ambient;
        glm::vec3 m_diffuse;
        glm::vec3 m_specular;

        std::string pointlightindex;

	};
}