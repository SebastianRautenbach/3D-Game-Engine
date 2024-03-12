#pragma once
#include "entity sys/component.h"
#include "gl core/core shader.h"


namespace wizm {
    class directionallight_component : public lowlevelsys::core_component {
    public:
        directionallight_component(
            glm::vec3 ambient = glm::vec3(0.05f, 0.05f, 0.05f),
            glm::vec3 diffuse = glm::vec3(0.4f, 0.4f, 0.4f),
            glm::vec3 specular = glm::vec3(0.5f, 0.5f, 0.5f)
        );


        void component_preupdate();
        void component_update();
        void component_postupdate();

    public:

        core_gl_shader* shader;

        glm::vec3 m_ambient;
        glm::vec3 m_diffuse;
        glm::vec3 m_specular;
    };
}