#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace lowlevelsys
{
	class core_timer {

	public:

		void update_delta_time();
		float get_delta_time();

	private:
		float deltaTime = 0.0f;
		float lastFrame = 0.0f;
	};
}