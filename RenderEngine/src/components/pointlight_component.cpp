#include "entity sys/components/pointlight_component.h"

wizm::pointlight_component::pointlight_component(float constant, float linear, float quadratic, float radius, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
    :light_component(ambient, diffuse, specular)
{
    m_component_type = ePointLight;

    m_constant = constant;
    m_linear = linear;
    m_quadratic = quadratic;

    m_radius = radius;
}

wizm::pointlight_component::~pointlight_component()
{
   
}

void wizm::pointlight_component::component_preupdate()
{

}

void wizm::pointlight_component::component_update(float delta_time, std::shared_ptr<core_gl_shader>& shader)
{
    
    //const std::string base_index = "pointLights[" + std::to_string(light_index) + "]";
    //
    //
    //const std::string position_property = base_index + ".position";
    //const std::string ambient_property = base_index + ".ambient";
    //const std::string diffuse_property = base_index + ".diffuse";
    //const std::string specular_property = base_index + ".specular";
    //const std::string constant_property = base_index + ".constant";
    //const std::string linear_property = base_index + ".linear";
    //const std::string quadratic_property = base_index + ".quadratic";
    //const std::string radius_property = base_index + ".radius";
    //
    //
    //const glm::vec3 world_position = get_world_position();
    //
    //
    //shader->setVec3(position_property, world_position);
    //shader->setVec3(ambient_property, m_ambient * glm::vec3(m_brightness));
    //shader->setVec3(diffuse_property, m_diffuse);
    //shader->setVec3(specular_property, m_specular);
    //shader->setFloat(constant_property, m_constant);
    //shader->setFloat(linear_property, m_linear);
    //shader->setFloat(quadratic_property, m_quadratic);
    //shader->setFloat(radius_property, m_radius);


}

void wizm::pointlight_component::component_postupdate()
{
}

std::shared_ptr<lowlevelsys::core_component> wizm::pointlight_component::_copy() const
{
    auto new_pc_comp = std::make_shared<pointlight_component>();

    new_pc_comp->set_position(this->get_position());
    new_pc_comp->set_rotation(this->get_rotation());
    new_pc_comp->set_scale(this->get_scale());

    new_pc_comp->light_index = this->light_index + 1;
    new_pc_comp->m_ambient = this->m_ambient;
    new_pc_comp->m_constant = this->m_constant;
    new_pc_comp->m_diffuse = this->m_diffuse;
    new_pc_comp->m_is_active = this->m_is_active;
    new_pc_comp->m_is_visible = this->m_is_visible;
    new_pc_comp->m_linear = this->m_linear;
    new_pc_comp->m_quadratic = this->m_quadratic;
    new_pc_comp->m_radius = this->m_radius;
    new_pc_comp->m_specular = this->m_specular;

    return new_pc_comp;
}
