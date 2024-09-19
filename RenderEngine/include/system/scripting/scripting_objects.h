#pragma once
#ifndef SCRIPTING_OBJECTS
#define SCRIPTING_OBJECTS

#include <string>

namespace wizm_script
{
	/////////////////////////////////////////////////////////////////////////////// MATH
	struct vec2 {
		float x, y;

		vec2(float px, float py) : x(px), y(py) {}
		vec2() : x(0.0f), y(0.0f) {}
	};

	struct vec3 {
		float x, y, z;

		vec3(float px, float py, float pz) : x(px), y(py), z(pz) {}
		vec3() : x(0.0f), y(0.0f), z(0.0f) {}

		vec3 operator+(const vec3& other) const {
			return vec3(x + other.x, y + other.y, z + other.z);
		}

	};
}


#endif