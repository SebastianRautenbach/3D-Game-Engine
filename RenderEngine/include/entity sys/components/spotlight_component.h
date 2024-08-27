#pragma once
#include "light_component.h"

using namespace lowlevelsys;

namespace wizm {
    class spotlight_component : public light_component {
    public:
        spotlight_component(
            float constant = 1.0f,
            float linear = 0.09,
            float quadratic = 0.032f,
            float cutOff = glm::cos(glm::radians(10.0f)),
            float outerCutOff = glm::cos(glm::radians(15.0f)),
            glm::vec3 ambient = glm::vec3(0.00f, 0.00f, 0.0f),
            glm::vec3 diffuse = glm::vec3(1.0f, 1.0f, 1.0f),
            glm::vec3 specular = glm::vec3(1.0f, 1.0f, 1.0f)
        );


        void component_preupdate();
        void component_update();
        void component_postupdate();
        std::shared_ptr<core_component> _copy() const;



        //////////////////////////////////////////////////
        //////////  SERIALIZATION METHOD /////////////////
        //////////////////////////////////////////////////


        void read_saved_data(std::string parent_name, std::string index, filedata::ZER& save_t) override {
        }


        void save_data(std::string parent_name, std::string index, filedata::ZER& save_t) const override {
        }


    public:
        unsigned int light_index = 0;

        float m_constant;
        float m_linear;
        float m_quadratic;

        glm::vec3 m_direction;
        float m_cutOff;
        float m_outerCutOff;



        std::string pointlightindex;



    };
}