#include "entity sys/component.h"
#include <iostream>

lowlevelsys::core_component::core_component()
{
	component_tags = new wizm::core_tag();
}


lowlevelsys::core_component::~core_component()
{
	delete component_tags;
}

void lowlevelsys::core_component::remove_component()
{
}