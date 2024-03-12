#include "entity sys/components/pointlight_component.h"

wizm::pointlight_component::pointlight_component(float constant, float linear, float quadratic, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
{
    m_component_type = ePointLight;

    m_constant = constant;
    m_linear = linear;
    m_quadratic = quadratic;

    m_ambient = ambient;
    m_diffuse = diffuse;
    m_specular = specular;

    
}

void wizm::pointlight_component::component_preupdate()
{

}

void wizm::pointlight_component::component_update()
{
    
    pointlightindex = "pointLights["
        + std::to_string(light_index) + "]";
    
    shader->setVec3(pointlightindex + ".position", m_position);
    shader->setVec3(pointlightindex + ".ambient", 0.05f, 0.05f, 0.05f);
    shader->setVec3(pointlightindex + ".diffuse", 0.8f, 0.8f, 0.8f);
    shader->setVec3(pointlightindex + ".specular", 1.0f, 1.0f, 1.0f);
    shader->setFloat(pointlightindex + ".constant", 1.0f);
    shader->setFloat(pointlightindex + ".linear", 0.09f);
    shader->setFloat(pointlightindex + ".quadratic", 0.032f);

}

void wizm::pointlight_component::component_postupdate()
{
}
