#include "entity sys/components/pointlight_component.h"

wizm::pointlight_component::pointlight_component(float constant, float linear, float quadratic, float radius, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
{
    m_component_type = ePointLight;

    m_constant = constant;
    m_linear = linear;
    m_quadratic = quadratic;

    m_ambient = ambient;
    m_diffuse = diffuse;
    m_specular = specular;

    m_radius = radius;
}

wizm::pointlight_component::~pointlight_component()
{
   
}

void wizm::pointlight_component::component_preupdate()
{

}

void wizm::pointlight_component::component_update()
{
    
    const std::string base_index = "pointLights[" + std::to_string(light_index) + "]";

    
    const std::string position_property = base_index + ".position";
    const std::string ambient_property = base_index + ".ambient";
    const std::string diffuse_property = base_index + ".diffuse";
    const std::string specular_property = base_index + ".specular";
    const std::string constant_property = base_index + ".constant";
    const std::string linear_property = base_index + ".linear";
    const std::string quadratic_property = base_index + ".quadratic";
    const std::string radius_property = base_index + ".radius";

    
    const glm::vec3 world_position = get_world_position();

    
    shader->setVec3(position_property, world_position);
    shader->setVec3(ambient_property, m_ambient);
    shader->setVec3(diffuse_property, m_diffuse);
    shader->setVec3(specular_property, m_specular);
    shader->setFloat(constant_property, m_constant);
    shader->setFloat(linear_property, m_linear);
    shader->setFloat(quadratic_property, m_quadratic);
    shader->setFloat(radius_property, m_radius);


}

void wizm::pointlight_component::component_postupdate()
{
}
