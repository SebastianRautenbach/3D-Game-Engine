#include "entity sys/components/directionallight_component.h"

wizm::directionallight_component::directionallight_component( glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
{
		m_component_type = eDirectionalLight;
		m_ambient = ambient;
		m_diffuse = diffuse;
		m_specular = specular;
}

void wizm::directionallight_component::component_preupdate()
{
}

void wizm::directionallight_component::component_update()
{
	shader->setVec3("dirLight.direction", get_rotation());
	shader->setVec3("dirLight.ambient", m_ambient);
	shader->setVec3("dirLight.diffuse", m_diffuse);
	shader->setVec3("dirLight.specular", m_specular);
}

void wizm::directionallight_component::component_postupdate()
{
}
