#include "entity sys/components/light_component.h"

wizm::light_component::light_component(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
	:m_ambient(ambient), m_diffuse(diffuse), m_specular(specular)
{
}
