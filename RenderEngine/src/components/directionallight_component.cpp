#include "entity sys/components/directionallight_component.h"

wizm::directionallight_component::directionallight_component( glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
{
		m_component_type = eDirectionalLight;
		glm::vec3 m_ambient = ambient;
		glm::vec3 m_diffuse = diffuse;
		glm::vec3 m_specular = specular;
}

void wizm::directionallight_component::component_preupdate()
{
}

void wizm::directionallight_component::component_update()
{
	shader->setVec3("dirLight.direction", m_rotation);
	shader->setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
	shader->setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
	shader->setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
}

void wizm::directionallight_component::component_postupdate()
{
}
