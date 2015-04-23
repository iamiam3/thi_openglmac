/*
 * controller.h
 *
 *  Created on: 23.04.2015
 *      Author: robert
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "window.h"
#include "mesh.h"
#include <glfw/glfw3.h>
#include <iostream>

class Controller {
public:
	Controller(Window* p_window, Mesh* p_mesh);
	virtual ~Controller();

	void setDeltaTime(float p_deltaTime);
	void checkInput();
private:
	Window* mc_windowPointer;
	Mesh* mc_meshPointer;
	glm::vec3 mc_position;
	float mc_horizontalAngle;
	float mc_verticalAngle;
	float mc_horizontalAngleBuffer;
	float mc_verticalAngleBuffer;
	float mc_fov;
	float mc_speed;
	float mc_mousespeed;
	glm::vec3 mc_right;
	glm::vec3 mc_up;
	glm::vec3 mc_viewDirection;
	float mc_deltaTime;
	double mc_mousePosBufferX;
	double mc_mousePosBufferY;

	void updateProjectionMatrix();
	void updateViewMatrix();
	void updateOrientation();
};

#endif /* CONTROLLER_H_ */
