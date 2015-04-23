/*
 * mesh.cpp
 *
 *  Created on: 19.04.2015
 *      Author: robert
 */

#include "mesh.h"

Mesh::Mesh(GLuint p_shaderProgramID) {
	// Save shader program ID
	mc_shaderProgramID = p_shaderProgramID;

	// Create Vertex Array Object (VAO)
	GLuint m_vertexArrayObject;
	glGenVertexArrays(1, &m_vertexArrayObject);
	// Set vertexArrayObject as current VAO
	glBindVertexArray(m_vertexArrayObject);

	// Create Vertex Buffer Objects (VBOs)
	glGenBuffers(1, &mc_vertexBufferObject);
	// Set vertexBufferObject as current VBO
	glBindBuffer(GL_ARRAY_BUFFER, mc_vertexBufferObject);
}

Mesh::~Mesh() {
}

void Mesh::drawMesh() {
		updateViewProjectionMatrix();

		// Attribute buffer: vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, mc_vertexBufferObject);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		for (int i = 0; i < mc_objectList.size(); i++) {
			// Send vertice data of object to OpenGL
			glBufferData(	GL_ARRAY_BUFFER,
							mc_objectList[i]->getVertices().size() * sizeof(glm::vec3),
							&mc_objectList[i]->getVertices()[0],
							GL_STATIC_DRAW);
			// Send viewProjection-matrix to vertex shader
			GLuint m_matrixID = glGetUniformLocation(mc_shaderProgramID, "vp");
			glUniformMatrix4fv(m_matrixID, 1, GL_FALSE, &mc_viewProjectionMatrix[0][0]);
			// Send translation matrix to vertex shader
			m_matrixID = glGetUniformLocation(mc_shaderProgramID, "tm");
			glUniformMatrix4fv(m_matrixID, 1, GL_FALSE, &mc_objectList[i]->getTransformationMatrix()[0][0]);
			// Send color vector to fragment shader
			GLuint m_vectorID = glGetUniformLocation(mc_shaderProgramID, "cv");
			glUniform3fv(m_vectorID, 1, mc_objectList[i]->getColor());

			// Draw objects
			glDrawArrays(
					mc_objectList[i]->getVertexType(),
					0,
					mc_objectList[i]->getVertices().size());
		}

		glDisableVertexAttribArray(0);
}

void Mesh::addObject(Object* p_objectPointer) {
	// Add object to list
	mc_objectList.push_back(p_objectPointer);
}

void Mesh::addGrid() {
	std::vector<glm::vec3> m_gridVertices;
	float scope = 30.0f;
	for ( float x = -scope; x <= scope; x +=1.0f ) {
		m_gridVertices.push_back(glm::vec3(x,0,-scope));
		m_gridVertices.push_back(glm::vec3(x,0,scope));
	}
	for ( float z = -scope; z <= scope; z+=1.0f ) {
		m_gridVertices.push_back(glm::vec3(-scope,0,z));
		m_gridVertices.push_back(glm::vec3(scope,0,z));
	}
	static Object mc_gridObject(m_gridVertices, glm::vec3(0,0,0), GL_LINES);
	mc_gridObject.setColor(0.5f,0.5f,0.5f);
	addObject(&mc_gridObject);
}

void Mesh::updateViewProjectionMatrix() {
	mc_viewProjectionMatrix = mc_projectionMatrix * mc_viewMatrix;
}

void Mesh::setViewMatrix(glm::mat4 p_viewMatrix) {
	mc_viewMatrix = p_viewMatrix;
	updateViewProjectionMatrix();
}

void Mesh::setProjectionMatrix(glm::mat4 p_projectionMatrix) {
	mc_projectionMatrix = p_projectionMatrix;
	updateViewProjectionMatrix();
}
