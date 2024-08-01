#include "entity sys/components/directionallight_component.h"

wizm::directionallight_component::directionallight_component(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
{
	m_component_type = eDirectionalLight;
	m_ambient = ambient;
	m_diffuse = diffuse;
	m_specular = specular;
}

wizm::directionallight_component::~directionallight_component()
{
	// the light doesnt actually get deleted
	// we fake it by blacking everything.
	shader->setVec3("dirLight.ambient", glm::vec3(0));
	shader->setVec3("dirLight.diffuse", glm::vec3(0));
	shader->setVec3("dirLight.specular", glm::vec3(0));
}

void wizm::directionallight_component::component_preupdate()
{

}

void wizm::directionallight_component::component_update()
{

	shader->setVec3("dirLight.direction", get_world_rotation());
	shader->setVec3("dirLight.ambient", m_ambient);
	shader->setVec3("dirLight.diffuse", m_diffuse);
	shader->setVec3("dirLight.specular", m_specular);
}

void wizm::directionallight_component::component_postupdate()
{
}

std::shared_ptr<core_component> wizm::directionallight_component::_copy() const
{
	auto new_dl_comp = std::make_shared<directionallight_component>();

	new_dl_comp->set_position(this->get_position());
	new_dl_comp->set_rotation(this->get_rotation());
	new_dl_comp->set_scale(this->get_scale());

	new_dl_comp->m_ambient = this->m_ambient;
	new_dl_comp->m_diffuse = this->m_diffuse;
	new_dl_comp->m_is_active = this->m_is_active;
	new_dl_comp->m_is_visible = this->m_is_visible;
	new_dl_comp->m_specular = this->m_specular;
	new_dl_comp->shader = this->shader;

	return new_dl_comp;
}