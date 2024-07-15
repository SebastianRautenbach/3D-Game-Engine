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


        //////////////////////////////////////////////////
        //////////  SERIALIZATION METHOD /////////////////
        //////////////////////////////////////////////////


        void save_data(std::string parent_name, std::string index) const override {

            filedata::ZER save_;
            save_.read_file_cntx();

            save_[parent_name]["pointlight" + index]["transform"]["position"].set_float("x", {get_position().x});
            save_[parent_name]["pointlight" + index]["transform"]["position"].set_float("y", { get_position().y });
            save_[parent_name]["pointlight" + index]["transform"]["position"].set_float("z", { get_position().z });

            save_[parent_name]["pointlight" + index]["transform"]["rotation"].set_float("x", { get_rotation().x });
            save_[parent_name]["pointlight" + index]["transform"]["rotation"].set_float("y", { get_rotation().y });
            save_[parent_name]["pointlight" + index]["transform"]["rotation"].set_float("z", { get_rotation().z });

            save_[parent_name]["pointlight" + index]["transform"]["scale"].set_float("x", { get_scale().x });
            save_[parent_name]["pointlight" + index]["transform"]["scale"].set_float("y", { get_scale().y });
            save_[parent_name]["pointlight" + index]["transform"]["scale"].set_float("z", { get_scale().z });
            
            save_[parent_name]["pointlight" + index]["light"].set_float("m_constant", { m_constant });
            save_[parent_name]["pointlight" + index]["light"].set_float("linear", { m_linear });
            save_[parent_name]["pointlight" + index]["light"].set_float("m_quadratic", { m_quadratic });
            save_[parent_name]["pointlight" + index]["light"].set_float("m_radius", { m_radius });

            save_[parent_name]["pointlight" + index]["light"].set_float("m_ambient", { m_ambient.x,m_ambient.y,m_ambient.z });
            save_[parent_name]["pointlight" + index]["light"].set_float("m_diffuse", { m_diffuse.x,m_diffuse.y,m_diffuse.z });
            save_[parent_name]["pointlight" + index]["light"].set_float("m_specular", { m_specular.x,m_specular.y,m_specular.z });
            save_[parent_name]["pointlight" + index]["light"].set_string("pointlightindex", {pointlightindex});
            save_[parent_name]["pointlight" + index]["light"].set_int("light_index", { static_cast<int>(light_index)});


            save_.save_file(save_);


        }
    
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