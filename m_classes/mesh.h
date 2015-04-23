/*
 * mesh.h
 *
 *  Created on: 19.04.2015
 *      Author: robert
 */

#ifndef MESH_H_
#define MESH_H_

#include <GL/glew.h>
#include "object.h"
#include <vector>
#include <glm/glm.hpp>
#include "window.h"
//#include "directionEnum.h"
// tmp
#include <iostream>

class Mesh {
public:
	Mesh(GLuint p_shaderProgramID);
	virtual ~Mesh();

	void setViewMatrix(glm::mat4 p_viewMatrix);
	void setProjectionMatrix(glm::mat4 p_projectionMatrix);

	void drawMesh();
	void addObject(Object* p_objectPointer);
	void addGrid();
private:
	GLuint mc_vertexBufferObject;
	GLuint mc_shaderProgramID;
	std::vector<Object*> mc_objectList;
	glm::mat4 mc_viewProjectionMatrix;
	glm::mat4 mc_viewMatrix;
	glm::mat4 mc_projectionMatrix;

	void updateViewProjectionMatrix();
};

#endif /* MESH_H_ */
