#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "system/3d_core_camera.h"
#include <iostream>

namespace wizm {

	//////////////////////////////////////////////////////////////////////////
	// DEFAULT CONSTRUCTOR
	//////////////////////////////////////////////////////////////////////////

	//-----------------------------------------------------------------------
	
	core_3d_camera::core_3d_camera(float afWidth, float afHeight)
		:mfScreenWidth(afWidth), mfScreenHeight(afHeight)
	{
		mvPosition = glm::vec3(.0f);

		mfFOV = glm::radians(70.0f);
		mfAspect = 4.0f / 3.0f;
		mfFarClipPlane = 1000.0f;
		mfNearClipPlane = 0.05f;

		mfPitch = 0;
		mfYaw = 0;
		mfRoll = 0;
		mfSensitivity = 0.1f;

		mbViewUpdated = true;
		mbProjectionUpdated = true;
		mbMoveUpdated = true;

		mbInfFarPlane = true;

		
 		mvPitchLimits = glm::vec2(3.14f / 2.0f, -3.14f / 2.0f);
 		mvYawLimits = glm::vec2(0, 0);
	}
	
	
	//-----------------------------------------------------------------------

	//////////////////////////////////////////////////////////////////////////
	// PUBLIC METHODS
	//////////////////////////////////////////////////////////////////////////

	//-----------------------------------------------------------------------

	
	
	void core_3d_camera::SetPosition(const glm::vec3& avPos)
	{
		mvPosition = avPos;
		mbViewUpdated = true;
	}

	//-----------------------------------------------------------------------

	glm::vec3 core_3d_camera::get_front_view()
	{
		glm::vec3 front;
		front.x = cos(mfYaw) * cos(mfPitch);
		front.y = sin(mfPitch);
		front.z = sin(mfYaw) * cos(mfPitch);
		front = glm::normalize(front);

		return front;
	}



	glm::vec3 core_3d_camera::get_up_view()
	{
		glm::vec3 forward = get_front_view();
		glm::vec3 worldUp(0, 1, 0); 
		glm::vec3 right = glm::normalize(glm::cross(forward, worldUp));
		glm::vec3 up = glm::cross(right, forward); 
		return glm::normalize(up);
	}



	glm::vec3 core_3d_camera::get_right_view() 
	{
		glm::vec3 forward = get_front_view();
		glm::vec3 worldUp(0, 1, 0);
		return glm::normalize(glm::cross(forward, worldUp));
	}


	//-----------------------------------------------------------------------

	void core_3d_camera::MoveForward(float afDist)
	{
		mvPosition += get_front_view() * afDist;
		mbViewUpdated = true;
	}

	void core_3d_camera::MoveRight(float afDist)
	{
		mvPosition += get_right_view() * afDist;
		mbViewUpdated = true;
	}

	void core_3d_camera::MoveUp(float afDist)
	{
		mvPosition += get_up_view() * afDist;
		mbViewUpdated = true;
	}

	//-----------------------------------------------------------------------


	void core_3d_camera::SetCameraWindowSize(float x, float y)
	{
		mfScreenWidth = x;
		mfScreenHeight = y;
	}


	void core_3d_camera::SetPitch(float afAngle)
	{
		mfPitch = afAngle;

		if (mvPitchLimits.x != 0 || mvPitchLimits.y != 0)
		{
			if (mfPitch > mvPitchLimits.x)mfPitch = mvPitchLimits.x;
			if (mfPitch < mvPitchLimits.y)mfPitch = mvPitchLimits.y;
		}

		mbViewUpdated = true; mbMoveUpdated = true;
	}


	void core_3d_camera::SetYaw(float afAngle)
	{
		mfYaw = afAngle;

		if (mvYawLimits.x != 0 || mvYawLimits.y != 0)
		{
			if (mfYaw > mvYawLimits.x)
				mfYaw = mvYawLimits.x;
			if (mfYaw < mvYawLimits.y)
				mfYaw = mvYawLimits.y;
		}

		mbViewUpdated = true; mbMoveUpdated = true;
	}

	


	void core_3d_camera::SetRoll(float afAngle)
	{
		mfRoll = afAngle;
		mbViewUpdated = true; mbMoveUpdated = true;
	}


	//-----------------------------------------------------------------------

	void core_3d_camera::AddPitch(float afAngle)
	{
		mfPitch += afAngle * mfSensitivity;

		if (mvPitchLimits.x != 0 || mvPitchLimits.y != 0)
		{

			if (mfPitch > mvPitchLimits.x)
				mfPitch = mvPitchLimits.x;
			if (mfPitch < mvPitchLimits.y)
				mfPitch = mvPitchLimits.y;
		}

		mbViewUpdated = true; mbMoveUpdated = true;
	}




	void core_3d_camera::AddYaw(float afAngle)
	{
		mfYaw += afAngle * mfSensitivity;

		if (mvYawLimits.x != 0 || mvYawLimits.y != 0)
		{
			if (mfYaw > mvYawLimits.x)
				mfYaw = mvYawLimits.x;
			if (mfYaw < mvYawLimits.y)
				mfYaw = mvYawLimits.y;
		}

		mbViewUpdated = true; mbMoveUpdated = true;
	}



	void core_3d_camera::AddRoll(float afAngle)
	{
		mfRoll += afAngle * mfSensitivity;
		mbViewUpdated = true; mbMoveUpdated = true;
	}

	//-----------------------------------------------------------------------

	const glm::mat4& core_3d_camera::GetViewMatrix()
	{
		
		return glm::lookAt(mvPosition, mvPosition + get_front_view(), get_up_view());
	}



	const glm::mat4& core_3d_camera::GetProjectionMatrix()
	{
		//return glm::perspective(glm::radians(45.0f), mfScreenWidth / mfScreenHeight, 0.1f, 100.0f);

		return glm::perspective(glm::radians(45.0f), mfAspect, 0.1f, 100.0f);
	}




	const glm::mat4& core_3d_camera::GetMoveMatrix()
	{
		return glm::mat4(0.f);
	}

}