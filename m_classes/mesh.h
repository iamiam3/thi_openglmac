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
// Tmp include
#include <iostream>

class Mesh {
public:
	Mesh(GLuint p_shaderProgramID);
	virtual ~Mesh();

	void updateMesh();
	void drawMesh();
	void addObject(Object* p_objectPointer);
private:
	std::vector<glm::vec3> mc_combinedVertices;
	GLuint mc_vertexBufferObject;
	GLuint mc_shaderProgramID;
	std::vector<Object*> mc_objectList;
};

#endif /* MESH_H_ */
