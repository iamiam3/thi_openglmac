/*
 * main.cpp
 *
 *  Created on: 18.04.2015
 *      Author: John Robert Westman
 */

#include <iostream>
#include "m_classes/window.h"
#include "m_classes/vertex.h"
#include "m_classes/shader.h"
#include <glm/gtc/matrix_transform.hpp>


int main(int argc, char **argv) {

	Window m_window(1024,768,"THI - Seminar - OpenGL Beispiel");



	// TODO MESH CLASS
	// TO BE EXPORTED INTO A MESH CLASS
	// DRAWING A TRIANGLE
	//#######################################################

	// Create Vertex Array Object (VAO)
	GLuint vertexArrayObject;
	glGenVertexArrays(1, &vertexArrayObject);
	// Set vertexArrayObject as current VAO
	glBindVertexArray(vertexArrayObject);

	Vertex vertices[] = { 	Vertex(glm::vec3(-1.0f, -1.0f, 0.0f)),
							Vertex(glm::vec3(1.0f, -1.0f, 0.0f)),
							Vertex(glm::vec3(0.0f, 1.0f, 0.0f)) };

	/*static const GLfloat vertices[] = {
			-1.0f, -1.0f, 0.0f,
			1.0f, -1.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
	};*/

	// Create Vertex Buffer Object (VBO)
	GLuint vertexBufferObject;
	// Generate 1 buffer, put the resulting identifier in the vertexbuffer
	glGenBuffers(1, &vertexBufferObject);
	// Set vertexBufferObject as current VBO
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	// Send the vertex data to OpenGL
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//#######################################################

	Shader shader("./res/basicShader");

	// Transformation
	glm::mat4 identityMatrix = glm::mat4(1.0f);
	// ModelViewProjection-Matrix
	glm::mat4 mvp = identityMatrix;
	// Send Matrix to the shader
	GLuint MatrixID = glGetUniformLocation(shader.getShaderProgramID(), "mvp");
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

	while ( !m_window.IsClosed() ) {
		//m_window.Clear(0.0f, 0.15f, 0.3f, 1.0f); // blue
		m_window.Clear(0.5f, 0.5f, 0.5f, 0.5f); // white

		shader.Bind();

		// TO BE EXPORTED INTO A MESH CLASS
		// DRAWING A TRIANGLE
		//#######################################################

		// First attribute buffer: vertices
		glEnableVertexAttribArray(0);
		//glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		// Draw the triangle
		glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices
		glDisableVertexAttribArray(0);

		//#######################################################

		m_window.Update();
	}

	return 0;
}


