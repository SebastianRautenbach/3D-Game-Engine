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
        ~directionallight_component();

        void component_preupdate();
        void component_update();
        void component_postupdate();


        //////////////////////////////////////////////////
        //////////  SERIALIZATION METHOD /////////////////
        //////////////////////////////////////////////////


        void save_data(std::string parent_name, std::string index) const override {

            filedata::ZER save_;
            save_.read_file_cntx();

            save_[parent_name]["directionallight" + index]["transform"]["position"].set_float("x", { get_position().x });
            save_[parent_name]["directionallight" + index]["transform"]["position"].set_float("y", { get_position().y });
            save_[parent_name]["directionallight" + index]["transform"]["position"].set_float("z", { get_position().z });

            save_[parent_name]["directionallight" + index]["transform"]["rotation"].set_float("x", { get_rotation().x });
            save_[parent_name]["directionallight" + index]["transform"]["rotation"].set_float("y", { get_rotation().y });
            save_[parent_name]["directionallight" + index]["transform"]["rotation"].set_float("z", { get_rotation().z });

            save_[parent_name]["directionallight" + index]["transform"]["scale"].set_float("x", { get_scale().x });
            save_[parent_name]["directionallight" + index]["transform"]["scale"].set_float("y", { get_scale().y });
            save_[parent_name]["directionallight" + index]["transform"]["scale"].set_float("z", { get_scale().z });

            save_[parent_name]["directionallight" + index]["light"].set_float("m_ambient", { m_ambient.x,m_ambient.y,m_ambient.z });
            save_[parent_name]["directionallight" + index]["light"].set_float("m_diffuse", { m_diffuse.x,m_diffuse.y,m_diffuse.z });
            save_[parent_name]["directionallight" + index]["light"].set_float("m_specular", { m_specular.x,m_specular.y,m_specular.z });


            save_.save_file(save_);


        }

    public:
        core_gl_shader* shader;

        glm::vec3 m_ambient;
        glm::vec3 m_diffuse;
        glm::vec3 m_specular;
    };
}