#include "entity sys/components/spotlight_component.h"

wizm::spotlight_component::spotlight_component(float constant, float linear, float quadratic,
	float cutOff, float outerCutOff, glm::vec3 ambient,
	glm::vec3 diffuse, glm::vec3 specular)
	: light_component(ambient, diffuse, specular)
{
    m_component_type = eSpotLight;

    m_constant = constant;
    m_linear = linear;
    m_quadratic = quadratic;

    m_cutOff = cutOff;
    m_outerCutOff = outerCutOff;
    
}

void wizm::spotlight_component::component_preupdate()
{
}

void wizm::spotlight_component::component_update()
{
    const std::string base_index = "spotLights[" + std::to_string(light_index) + "]";


    const std::string position_property = base_index + ".position";
    const std::string ambient_property = base_index + ".ambient";
    const std::string diffuse_property = base_index + ".diffuse";
    const std::string direction_property = base_index + ".direction";
    const std::string direction_cutOff = base_index + ".cutOff";
    const std::string direction_outerCutOff = base_index + ".outerCutOff";
    const std::string specular_property = base_index + ".specular";
    const std::string constant_property = base_index + ".constant";
    const std::string linear_property = base_index + ".linear";
    const std::string quadratic_property = base_index + ".quadratic";

    const glm::vec3 world_position = get_world_position();

    const glm::vec3 world_direction = get_world_forward_vector();


    shader->setVec3(position_property, world_position);
    shader->setVec3(ambient_property, m_ambient);
    shader->setVec3(diffuse_property, m_diffuse);
    shader->setVec3(specular_property, m_specular);
    shader->setFloat(constant_property, m_constant);
    shader->setFloat(linear_property, m_linear);
    shader->setFloat(quadratic_property, m_quadratic);
    shader->setVec3(direction_property, world_direction);
    shader->setFloat(direction_cutOff, m_cutOff);
    shader->setFloat(direction_outerCutOff, m_outerCutOff);
    
}

void wizm::spotlight_component::component_postupdate()
{
}

std::shared_ptr<core_component> wizm::spotlight_component::_copy() const
{
	return std::shared_ptr<core_component>();
}
