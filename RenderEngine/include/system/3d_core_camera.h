#pragma once
#include "gl core/core_camera.h"

namespace wizm {

	class core_3d_camera : public lowlevelsys::core_camera {

	public:

		core_3d_camera(float afWidth, float afHeight);
		~core_3d_camera() {};





		const glm::vec3& GetPosition()const { return mvPosition; }
		void SetPosition(const glm::vec3& avPos);

		/**
		 * Get the front vector that the camera is looking at
		 */

		glm::vec3 get_front_view();

		/**
		 * Get the up vector that the camera is looking at
		 */


		glm::vec3 get_up_view();

		/**
		 * Get the right vector that the camera is looking at
		 */

		glm::vec3 get_right_view();

		/**
		 * Move forward (or back) according to the move mode.
		 * \param afDist
		 */
		void MoveForward(float afDist);
		/**
		* Move right (or left) according to the move mode.
		* \param afDist
		*/
		void MoveRight(float afDist);
		/**
		* Move up (or down) according to the move mode.
		* \param afDist
		*/
		void MoveUp(float afDist);

		void SetFOV(float afAngle) { mfFOV = afAngle; mbProjectionUpdated = true; }
		float GetFOV() { return mfFOV; }

		void SetAspect(float afAngle) { mfAspect = afAngle; mbProjectionUpdated = true; }
		float GetAspect() { return mfAspect; }

		void SetFarClipPlane(float afX) { mfFarClipPlane = afX; mbProjectionUpdated = true; }
		float GetFarClipPlane() { return mfFarClipPlane; }

		void SetNearClipPlane(float afX) { mfNearClipPlane = afX; mbProjectionUpdated = true; }
		float GetNearClipPlane() { return mfNearClipPlane; }


		//////////////////////////////////////////////////
		////////// EULER ANGLES ROTATION /////////////////
		//////////////////////////////////////////////////

		void SetPitch(float afAngle);
		void SetYaw(float afAngle);
		void SetRoll(float afAngle);

		void AddPitch(float afAngle);
		void AddYaw(float afAngle);
		void AddRoll(float afAngle);

		float GetPitch() const { return mfPitch; }
		float GetYaw() const { return mfYaw; }
		float GetRoll() const { return mfRoll; }


		/**
		 * Set the limits within the pitch can move
		 * \param avLimits x = high limit and y low.If both are 0 limits are disabled.
		 */
		void SetPitchLimits(glm::vec2 avLimits) { mvPitchLimits = avLimits; }
		const glm::vec2& GetPitchLimits() { return mvPitchLimits; }
		/**
		* Set the limits within the yaw can move
		* \param avLimits x = high limit and y low. If both are 0 limits are disabled.
		*/
		void SetYawLimits(glm::vec2 avLimits) { mvYawLimits = avLimits; }
		const glm::vec2& GetYawLimits() { return mvYawLimits; }

		//////////////////////////////////////////////////
		////////// EULER ANGLES ROTATION /////////////////
		//////////////////////////////////////////////////

		const glm::mat4& GetViewMatrix();
		const glm::mat4& GetProjectionMatrix();

		const glm::mat4& GetMoveMatrix();



		// save data
		
		void SetModelViewMatrix() {};
		void SetProjectionMatrix() {};
		glm::vec3 GetEyePosition() { return glm::vec3(0.0f); }





	private:

		glm::vec3 mvPosition;

		float mfFOV;
		float mfAspect;
		float mfFarClipPlane;
		float mfNearClipPlane;
		float mfScreenWidth;
		float mfScreenHeight;

		float mfPitch;
		float mfYaw;
		float mfRoll;
		float mfSensitivity;
		glm::vec2 mvPitchLimits;
		glm::vec2 mvYawLimits;

	/*	core_node_3d mNode;*/

		bool mbInfFarPlane;

		bool mbViewUpdated;
		bool mbProjectionUpdated;
		bool mbMoveUpdated;
	};
}



