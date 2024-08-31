#include "entity sys/components/spotlight_component.h"

wizm::spotlight_component::spotlight_component(float constant, float linear, float quadratic,
	float cutOff, float outerCutOff, float distance, glm::vec3 ambient,
	glm::vec3 diffuse, glm::vec3 specular)
	: light_component(ambient, diffuse, specular)
{
    m_component_type = eSpotLight;

    m_constant = constant;
    m_linear = linear;
    m_quadratic = quadratic;

    m_cutOff = cutOff;
    m_outerCutOff = outerCutOff;

    m_distance = distance;
    
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
    const std::string distance_property = base_index + ".distance";

    glm::vec3 world_position = get_world_position();
    glm::vec3 world_rotation = get_world_rotation();
    glm::quat rotation_quat = glm::quat(glm::vec3(glm::radians(world_rotation.x), glm::radians(world_rotation.y), glm::radians(world_rotation.z)));
    glm::vec3 rotated_direction = glm::normalize(rotation_quat * glm::vec3(0.0f, -1.0f, 0.0f));

    shader->setVec3(position_property, world_position);
    shader->setVec3(direction_property, rotated_direction);
    shader->setVec3(ambient_property, m_ambient);
    shader->setVec3(diffuse_property, m_diffuse);
    shader->setVec3(specular_property, m_specular);
    shader->setFloat(constant_property, m_constant);
    shader->setFloat(linear_property, m_linear);
    shader->setFloat(quadratic_property, m_quadratic);
    shader->setFloat(direction_cutOff, m_cutOff);
    shader->setFloat(direction_outerCutOff, m_outerCutOff);
    shader->setFloat(distance_property, m_distance);
    
}

void wizm::spotlight_component::component_postupdate()
{
}

std::shared_ptr<core_component> wizm::spotlight_component::_copy() const
{
    auto new_sc_comp = std::make_shared<spotlight_component>();

    new_sc_comp->set_position(this->get_position());
    new_sc_comp->set_rotation(this->get_rotation());
    new_sc_comp->set_scale(this->get_scale());

    new_sc_comp->light_index = this->light_index + 1;
    new_sc_comp->m_ambient = this->m_ambient;
    new_sc_comp->m_constant = this->m_constant;
    new_sc_comp->m_diffuse = this->m_diffuse;
    new_sc_comp->m_is_active = this->m_is_active;
    new_sc_comp->m_is_visible = this->m_is_visible;
    new_sc_comp->m_linear = this->m_linear;
    new_sc_comp->m_quadratic = this->m_quadratic;
    new_sc_comp->m_specular = this->m_specular;
    new_sc_comp->m_outerCutOff = this->m_outerCutOff;
    new_sc_comp->m_cutOff = this->m_cutOff;
    new_sc_comp->shader = this->shader;

    return new_sc_comp;
}
