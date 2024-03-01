#include "system/timer.h"


namespace lowlevelsys {

	void core_timer::update_delta_time()
	{
		auto currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
	}

	float core_timer::get_delta_time()
	{
		return deltaTime;
	}
}
