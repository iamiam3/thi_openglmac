/*
 * controller.cpp
 *
 *  Created on: 23.04.2015
 *      Author: robert
 */

#include "controller.h"

Controller::Controller(Window* p_windowPointer, Mesh* p_meshPointer) {
	// Set initial camera/view data
	mc_position = glm::vec3(6,3,-5);
	mc_horizontalAngle = -50 * (M_PI / 180); // degree * pi / 180 == rad(degree);
	mc_horizontalAngleBuffer = mc_horizontalAngle;
	mc_verticalAngle = -10 * (M_PI / 180);
	mc_verticalAngleBuffer = mc_verticalAngle;
	mc_fov = 45.0f; // in degree
	mc_speed = 6.0f; // 3 unites / s
	mc_mousespeed = 0.005f;
	mc_deltaTime = 0.02f;
	mc_viewDirection = glm::vec3(
			cos(mc_verticalAngle) * sin(mc_horizontalAngle),
			sin(mc_verticalAngle),
			cos(mc_verticalAngle) * cos(mc_horizontalAngle)
	);
	mc_right = glm::vec3(
			sin(mc_horizontalAngle - 3.14f/2.0f),
			0,
			cos(mc_horizontalAngle - 3.14f/2.0f)
	);
	mc_up = glm::cross(mc_right,mc_viewDirection);
	mc_windowPointer = p_windowPointer;
	mc_meshPointer = p_meshPointer;
	updateProjectionMatrix();
	updateViewMatrix();
}

Controller::~Controller() {
}

void Controller::setDeltaTime(float p_deltaTime) {
	mc_deltaTime = p_deltaTime;
}

void Controller::checkInput() {
	// Zoom
	if (glfwGetKey(mc_windowPointer->getWindowPointer(), GLFW_KEY_R) == GLFW_PRESS) {
		mc_fov -= 0.02;
	}
	if (glfwGetKey(mc_windowPointer->getWindowPointer(), GLFW_KEY_F) == GLFW_PRESS) {
		mc_fov += 0.02;
	}

	// Orientation
	if (glfwGetMouseButton(mc_windowPointer->getWindowPointer(), GLFW_MOUSE_BUTTON_2) == GLFW_PRESS) {
		// If right mouse button is pressed: rotate on mouse movement
		updateOrientation();
	} else {
		// If right mouse button is released: update mouse position and angle buffers
		glfwGetCursorPos(mc_windowPointer->getWindowPointer(), &mc_mousePosBufferX, &mc_mousePosBufferY);
		mc_horizontalAngleBuffer = mc_horizontalAngle;
		mc_verticalAngleBuffer = mc_verticalAngle;
	}

	// Position
	if (glfwGetKey(mc_windowPointer->getWindowPointer(), GLFW_KEY_UP) == GLFW_PRESS
			|| glfwGetKey(mc_windowPointer->getWindowPointer(), GLFW_KEY_W) == GLFW_PRESS) {
		mc_position += mc_viewDirection * mc_deltaTime * mc_speed;
	}
	if (glfwGetKey(mc_windowPointer->getWindowPointer(), GLFW_KEY_DOWN) == GLFW_PRESS
			|| glfwGetKey(mc_windowPointer->getWindowPointer(), GLFW_KEY_S) == GLFW_PRESS) {
		mc_position -= mc_viewDirection * mc_deltaTime * mc_speed;
	}
	if (glfwGetKey(mc_windowPointer->getWindowPointer(), GLFW_KEY_RIGHT) == GLFW_PRESS
			|| glfwGetKey(mc_windowPointer->getWindowPointer(), GLFW_KEY_D) == GLFW_PRESS) {
		mc_position += mc_right * mc_deltaTime * mc_speed;
	}
	if (glfwGetKey(mc_windowPointer->getWindowPointer(), GLFW_KEY_LEFT) == GLFW_PRESS
			|| glfwGetKey(mc_windowPointer->getWindowPointer(), GLFW_KEY_A) == GLFW_PRESS) {
		mc_position -= mc_right * mc_deltaTime * mc_speed;
	}
	if (glfwGetKey(mc_windowPointer->getWindowPointer(), GLFW_KEY_T) == GLFW_PRESS) {
		mc_position += mc_viewDirection * mc_deltaTime * mc_speed * 10.0f;
	}
	if (glfwGetKey(mc_windowPointer->getWindowPointer(), GLFW_KEY_G) == GLFW_PRESS) {
		mc_position -= mc_viewDirection * mc_deltaTime * mc_speed * 10.0f;
	}

	updateViewMatrix();
	updateProjectionMatrix();
}

void Controller::updateProjectionMatrix() {
	mc_meshPointer->setProjectionMatrix(glm::perspective(mc_fov, 4.0f/3.0f, 0.1f, 100.0f));
}

void Controller::updateViewMatrix() {
	mc_meshPointer->setViewMatrix(glm::lookAt(
		mc_position,
		mc_position+mc_viewDirection,
		mc_up
	));
}

void Controller::updateOrientation() {
	double m_mousePosX, m_mousePosY;
	glfwGetCursorPos(mc_windowPointer->getWindowPointer(), &m_mousePosX, &m_mousePosY);
	mc_horizontalAngle = mc_horizontalAngleBuffer + mc_mousespeed * float(mc_mousePosBufferX - m_mousePosX);
	mc_verticalAngle = mc_verticalAngleBuffer + mc_mousespeed * float(mc_mousePosBufferY - m_mousePosY);
	mc_viewDirection = glm::vec3(
			cos(mc_verticalAngle) * sin(mc_horizontalAngle),
			sin(mc_verticalAngle),
			cos(mc_verticalAngle) * cos(mc_horizontalAngle)
	);
	mc_right = glm::vec3(
			sin(mc_horizontalAngle - 3.14f/2.0f),
			0,
			cos(mc_horizontalAngle - 3.14f/2.0f)
	);
	mc_up = glm::cross(mc_right,mc_viewDirection);
}
