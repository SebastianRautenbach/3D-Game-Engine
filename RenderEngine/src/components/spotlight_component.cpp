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

void wizm::spotlight_component::component_update(float delta_time, std::shared_ptr<core_gl_shader>& shader)
{

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
    new_sc_comp->m_distance = this->m_distance;

    return new_sc_comp;
}
