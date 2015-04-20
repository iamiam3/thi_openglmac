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
}

Mesh::~Mesh() {
}

void Mesh::drawMesh() {
		// Attribute buffer: vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, mc_vertexBufferObject);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		// Draw mesh
		glDrawArrays(GL_TRIANGLES, 0, mc_combinedVertices.size()); // Starting from vertex 0; 3 vertices
		glDisableVertexAttribArray(0);
}

void Mesh::updateMesh() {

}

void Mesh::addObject(Object* p_objectPointer) {
//	std::vector<glm::vec3> mc_combinedVertices;
//	GLuint mc_vertexBufferObject;
//	GLuint mc_shaderProgramID;
//	std::vector<Object*> mc_objectList;

	// Add object to list
	mc_objectList.push_back(p_objectPointer);
	// Add object vertices to the combinedVertices
	for (int i = 0; i < p_objectPointer->getVertices().size(); i++) {
		mc_combinedVertices.push_back(p_objectPointer->getVertices()[i]);
	}
	// Set vertexBufferObject as current VBO
	glBindBuffer(GL_ARRAY_BUFFER, mc_vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, mc_combinedVertices.size() * sizeof(glm::vec3), &mc_combinedVertices[0], GL_STATIC_DRAW);
}
