#pragma once

#include "base.hpp"
#include "Math/Math.hpp"

namespace LaughCrab {
	class CameraCustom
	{
	public:
		enum Camera_Movement {
			FORWARD,
			BACKWARD,
			LEFT,
			RIGHT
		};

	public:
		~CameraCustom() = default;

		CameraCustom(LaughMath::Vector3 position = LaughMath::Vector3{ 0.0f, 0.0f, 0.0f },
			LaughMath::Vector3 up = LaughMath::Vector3{ 0.0f, 1.0f, 0.0f }, GLfloat yaw = YAW,
			GLfloat pitch = PITCH) :
			front(LaughMath::Vector3{0.0f, 0.0f, 1.0f}), movementSpeed(SPEED),
			mouseSensitivity(SENSITIVTY), zoom(ZOOM),
			position(position), worldUp(up), yaw(yaw), pitch(pitch)
		{
			updateCameraVectors();
		}

		CameraCustom(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY,
			GLfloat upZ, GLfloat yaw, GLfloat pitch) :
			front(LaughMath::Vector3{ 0.0f, 0.0f, 1.0f }),
			movementSpeed(SPEED), mouseSensitivity(SENSITIVTY), zoom(ZOOM),
			position(LaughMath::Vector3{ posX, posY, posZ }),
			worldUp(LaughMath::Vector3{ upX, upY, upZ }), yaw(yaw), pitch(pitch)
		{
			updateCameraVectors();
		}

		const LaughMath::Matrix44 getViewMatrix(bool bglmLookAt = true) const
		{
			return LaughMath::LookAtViewRH(position, position + front, up);
		}

		void setYaw(GLfloat yaw) { this->yaw = yaw; }
		void setYawDelta(GLfloat delta) { this->yaw += delta; }
		void setPitch(GLfloat pitch) { this->pitch = pitch; }
		void setPtichDelta(GLfloat delta) { this->pitch += delta; }

		const GLfloat getMoveSpeed() const { return movementSpeed; }
		const GLfloat getMouseSensi() const { return mouseSensitivity; }
		const GLfloat getViewZoom() const { return zoom; }
		const LaughMath::Vector3 getPositon() const { return position; }
		const LaughMath::Vector3 getFront() const { return front; }

		void processKeyboard(Camera_Movement direction, GLfloat deltaTime);

		void processMouseMovement(GLfloat xoffset, GLfloat yoffset,
			GLboolean constrainPitch = true);

		void processMouseScroll(GLfloat yoffset);

	private:
		// Camera Attributes
		LaughMath::Vector3 position;
		LaughMath::Vector3 front;
		LaughMath::Vector3 up;
		LaughMath::Vector3 right;
		LaughMath::Vector3 worldUp;

		// Eular Angles
		GLfloat yaw;
		GLfloat pitch;
	private:
		// Camera options
		GLfloat movementSpeed;
		GLfloat mouseSensitivity;
		GLfloat zoom;
	private:
		// Default camera values
		static constexpr GLfloat YAW = -90.0f;
		static constexpr GLfloat PITCH = 0.0f;
		static constexpr GLfloat SPEED = 0.01f;
		static constexpr GLfloat SENSITIVTY = 0.25f;
		static constexpr GLfloat ZOOM = 45.0f;
	private:
		// Calculates the front vector from the Camera's (updated) Eular Angles
		void updateCameraVectors();
	};
}
