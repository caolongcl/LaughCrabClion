#include "CameraCustom.hpp"
#include "Math/Math.hpp"
#include <iostream>

using namespace LaughCrab;
using namespace LaughCrab::LaughMath;
using namespace std;

namespace LaughCrab {

	void CameraCustom::processKeyboard(Camera_Movement direction, GLfloat deltaTime)
	{
		GLfloat velocity = movementSpeed * deltaTime;

		if (direction == FORWARD)
			position += front * velocity;
		if (direction == BACKWARD)
			position -= front * velocity;
		if (direction == LEFT)
			position -= right * velocity;
		if (direction == RIGHT)
			position += right * velocity;
	}

	void CameraCustom::processMouseMovement(GLfloat xoffset, GLfloat yoffset,
		GLboolean constrainPitch)
	{
		xoffset *= mouseSensitivity;
		yoffset *= mouseSensitivity;

		yaw += xoffset;
		pitch += yoffset;

		// Make sure that when pitch is out of bounds, screen doesn't get flipped
		if (constrainPitch)
		{
			if (pitch > 89.0f)
				pitch = 89.0f;
			if (pitch < -89.0f)
				pitch = -89.0f;
		}

		// Update Front, Right and Up Vectors using the updated Eular angles
		updateCameraVectors();
	}

	//fov
	void CameraCustom::processMouseScroll(GLfloat yoffset)
	{
		if (zoom >= 1.0f && zoom <= 45.0f)
			zoom -= yoffset;
		if (zoom <= 1.0f)
			zoom = 1.0f;
		if (zoom >= 45.0f)
			zoom = 45.0f;
	}

	void CameraCustom::updateCameraVectors()
	{
		// Calculate the new Front vector
		Vector3 newfront;
		newfront[i_x] = cos(Radians(yaw)) * cos(Radians(pitch));
		newfront[i_y] = sin(Radians(pitch));
		newfront[i_z] = sin(Radians(yaw)) * cos(Radians(pitch));
		//cout << "\nnew front " << newfront;
		front = Normalize(newfront);
		//cout << "\nfront " << front;
		//cout << "\nwup " << up;
		Vector3 crossfu = Cross(front, worldUp);
		//cout << "\ncrossfu" << crossfu;
		// Also re-calculate the Right and Up vector
		right = Normalize(crossfu);
		//cout << "\nright " << right;
		Vector3 crossrf = Cross(right, front);
		//cout << "\ncrossrf " << right;
		up = Normalize(crossrf);
		//cout << "\nup " << up;
	}
}