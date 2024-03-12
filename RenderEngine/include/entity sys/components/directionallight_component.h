#pragma once
#include "entity sys/component.h"
#include "gl core/core shader.h"



namespace wizm {
    class directionallight_component : public lowlevelsys::core_component {
    public:
        directionallight_component(
         

        );


        void component_preupdate();
        void component_update();
        void component_postupdate();

    public:

        core_gl_shader* shader;


        glm::vec3 m_direction;
        glm::vec3 m_ambient;
        glm::vec3 m_diffuse;
        glm::vec3 m_specular;
    };
}