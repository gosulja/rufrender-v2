#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

enum CameraMovement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
};

class Camera {
public:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	float yaw = -90.0f;
	float pitch = 0.0f;
	float speed = 2.5f;
	float sensitivity = 0.1f;
	float zoom = 45.0f;

	Camera(
		glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
		float yaw = -90.0f, float pitch = 0.0f
	) : front(glm::vec3(0.0f, 0.0f, -1.0f)), speed(2.5f), sensitivity(0.1f), zoom(45.0f) {
		this->position = position;
		this->worldUp = up;
		this->yaw = yaw;
		this->pitch = pitch;

		updateCameraVectors();
	}

	Camera(
		float posX,
		float posY,
		float posZ,
		float upX,
		float upY,
		float upZ,
		float yaw,
		float pitch
	) : front(glm::vec3(0.0f, 0.0f, -1.0f)), speed(speed), sensitivity(sensitivity), zoom(zoom) {
		position = glm::vec3(posX, posY, posZ);
		worldUp = glm::vec3(upX, upY, upZ);
		yaw = yaw;
		pitch = pitch;

		updateCameraVectors();
	}

	glm::mat4 GetViewMatrix() {
		return glm::lookAt(position, position + front, up);
	}

	void ProcessKeyboard(CameraMovement direction, float deltaTime) {
		float velocity = speed * deltaTime;
		switch (direction) {
			case FORWARD:
				position += front * velocity;
				break;

			case BACKWARD:
				position -= front * velocity;
				break;

			case LEFT:
				position -= right * velocity;
				break;

			case RIGHT:
				position += right * velocity;
				break;
		}
	}

	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true) {
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		yaw   += xoffset;
		pitch += yoffset;

		if (constrainPitch) {
			if (pitch > 89.0f)
				pitch = 89.0f;
			if (pitch < -89.0f)
				pitch = -89.0f;
		}

		updateCameraVectors();
	}

	void ProcessMouseScroll(float yoffset) {
		zoom -= (float)yoffset;

		std::cout << zoom << std::endl;

		if (zoom < 1.0f)
			zoom = 1.0f;
		if (zoom > 120.0f)
			zoom = 120.0f;
	}

private:
	void updateCameraVectors() {
		glm::vec3 newFront;
		newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		newFront.y = sin(glm::radians(pitch));
		newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		front = glm::normalize(newFront);

		right = glm::normalize(glm::cross(front, worldUp));
		up = glm::normalize(glm::cross(right, front));
	}
};

#endif CAMERA_HPP