#pragma once
#include <string>

namespace wizm_script
{
	/////////////////////////////////////////////////////////////////////////////// MATH
	struct vec2 {
		float x, y;

		vec2() : x(0.0f), y(0.0f) {}
	};

	struct vec3 {
		float x, y, z;

		vec3() : x(0.0f), y(0.0f), z(0.0f) {}
	};


	/////////////////////////////////////////////////////////////////////////////// COMPONENT

	struct component {
		std::string name;
		int index = 0;
	};
}