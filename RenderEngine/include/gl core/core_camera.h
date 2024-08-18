#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace lowlevelsys {

	class core_camera {

	public:

		virtual void SetModelViewMatrix() = 0;
		virtual void SetProjectionMatrix() = 0;
		virtual glm::vec3 GetEyePosition() = 0;


	};
}