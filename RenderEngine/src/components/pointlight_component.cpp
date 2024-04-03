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
    
    pointlightindex = "pointLights["
        + std::to_string(light_index) + "]";
  
    shader->setVec3(pointlightindex + ".position", get_world_position());
    shader->setVec3(pointlightindex + ".ambient", m_ambient);
    shader->setVec3(pointlightindex + ".diffuse", m_diffuse);
    shader->setVec3(pointlightindex + ".specular", m_specular);
    shader->setFloat(pointlightindex + ".constant", m_constant);
    shader->setFloat(pointlightindex + ".linear", m_linear);
    shader->setFloat(pointlightindex + ".quadratic", m_quadratic);
    shader->setFloat(pointlightindex + ".radius", m_radius);

}

void wizm::pointlight_component::component_postupdate()
{
}
