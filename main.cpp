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
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/transform.hpp>

// TODO IMPORTANT: SORT ALL THIS DRAWING STUFF OUT AND MOVE IT IN SEPERATE CLASSES


int main(int argc, char **argv) {

	Window m_window(1024,768,"THI - Seminar - OpenGL Beispiel");

	Shader shader("./res/basicShader");

	// TODO MESH CLASS
	// TO BE EXPORTED INTO A MESH CLASS
	// DRAWING A TRIANGLE
	//#######################################################

	// Create Vertex Array Object (VAO)
	GLuint vertexArrayObject;
	glGenVertexArrays(1, &vertexArrayObject);
	// Set vertexArrayObject as current VAO
	glBindVertexArray(vertexArrayObject);

	/*Vertex vertices[] = { 	Vertex(glm::vec3(-1.0f, -1.0f, 0.0f)),
							Vertex(glm::vec3(1.0f, -1.0f, 0.0f)),
							Vertex(glm::vec3(0.0f, 1.0f, 0.0f)) };*/

	static const GLfloat vertices[] = {
			    -1.0f,-1.0f,-1.0f, // triangle 1 : begin
    			-1.0f,-1.0f, 1.0f,
    			-1.0f, 1.0f, 1.0f, // triangle 1 : end
				1.0f, 1.0f,-1.0f, // triangle 2 : begin
				-1.0f,-1.0f,-1.0f,
				-1.0f, 1.0f,-1.0f, // triangle 2 : end
				1.0f,-1.0f, 1.0f,
				-1.0f,-1.0f,-1.0f,
				1.0f,-1.0f,-1.0f,
				1.0f, 1.0f,-1.0f,
				1.0f,-1.0f,-1.0f,
				-1.0f,-1.0f,-1.0f,
				-1.0f,-1.0f,-1.0f,
				-1.0f, 1.0f, 1.0f,
				-1.0f, 1.0f,-1.0f,
				1.0f,-1.0f, 1.0f,
				-1.0f,-1.0f, 1.0f,
				-1.0f,-1.0f,-1.0f,
				-1.0f, 1.0f, 1.0f,
				-1.0f,-1.0f, 1.0f,
				1.0f,-1.0f, 1.0f,
				1.0f, 1.0f, 1.0f,
				1.0f,-1.0f,-1.0f,
				1.0f, 1.0f,-1.0f,
				1.0f,-1.0f,-1.0f,
				1.0f, 1.0f, 1.0f,
				1.0f,-1.0f, 1.0f,
				1.0f, 1.0f, 1.0f,
				1.0f, 1.0f,-1.0f,
				-1.0f, 1.0f,-1.0f,
				1.0f, 1.0f, 1.0f,
				-1.0f, 1.0f,-1.0f,
				-1.0f, 1.0f, 1.0f,
				1.0f, 1.0f, 1.0f,
				-1.0f, 1.0f, 1.0f,
				1.0f,-1.0f, 1.0f,
				-2.0f, -1.0f, 2.0f,
				-2.0f, -1.0f, -2.0f,
				2.0f, -1.0f, 2.0f,
				-2.0f, -1.0f, -2.0f,
				2.0f, -1.0f, 2.0f,
				2.0f, -1.0f, -2.0f,
	};

	// One color for each vertex. They were generated randomly.
	static const GLfloat g_color_buffer_data[] = {
	    0.583f,  0.771f,  0.014f,
	    0.609f,  0.115f,  0.436f,
	    0.327f,  0.483f,  0.844f,
	    0.822f,  0.569f,  0.201f,
	    0.435f,  0.602f,  0.223f,
	    0.310f,  0.747f,  0.185f,
	    0.597f,  0.770f,  0.761f,
	    0.559f,  0.436f,  0.730f,
	    0.359f,  0.583f,  0.152f,
	    0.483f,  0.596f,  0.789f,
	    0.559f,  0.861f,  0.639f,
	    0.195f,  0.548f,  0.859f,
	    0.014f,  0.184f,  0.576f,
	    0.771f,  0.328f,  0.970f,
	    0.406f,  0.615f,  0.116f,
	    0.676f,  0.977f,  0.133f,
	    0.971f,  0.572f,  0.833f,
	    0.140f,  0.616f,  0.489f,
	    0.997f,  0.513f,  0.064f,
	    0.945f,  0.719f,  0.592f,
	    0.543f,  0.021f,  0.978f,
	    0.279f,  0.317f,  0.505f,
	    0.167f,  0.620f,  0.077f,
	    0.347f,  0.857f,  0.137f,
	    0.055f,  0.953f,  0.042f,
	    0.714f,  0.505f,  0.345f,
	    0.783f,  0.290f,  0.734f,
	    0.722f,  0.645f,  0.174f,
	    0.302f,  0.455f,  0.848f,
	    0.225f,  0.587f,  0.040f,
	    0.517f,  0.713f,  0.338f,
	    0.053f,  0.959f,  0.120f,
	    0.393f,  0.621f,  0.362f,
	    0.673f,  0.211f,  0.457f,
	    0.820f,  0.883f,  0.371f,
	    0.982f,  0.099f,  0.879f,
		0.0f,0.0f,0.0f,
		0.0f,0.0f,0.0f,
		0.0f,0.0f,0.0f,
		0.0f,0.0f,0.0f,
		0.0f,0.0f,0.0f,
		0.0f,0.0f,0.0f
	};

	GLuint colorbuffer;
	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

	// Create Vertex Buffer Object (VBO)
	GLuint vertexBufferObject;
	// Generate 1 buffer, put the resulting identifier in the vertexbuffer
	glGenBuffers(1, &vertexBufferObject);
	// Set vertexBufferObject as current VBO
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	// Send the vertex data to OpenGL
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//#######################################################



	float myAngle = 0.0f;
	int rotations = 2;
	float movementPosX = -1.0;
	bool movingForward = true;

	while ( !m_window.IsClosed() ) {
		//m_window.Clear(0.0f, 0.15f, 0.3f, 1.0f); // blue
		m_window.Clear(0.5f, 0.5f, 0.5f, 0.5f); // white

		shader.Bind();

		// TRANSFORMATION
		// Projection matrix
		glm::mat4 projection = glm::perspective(20.0f, 4.0f / 3.0f, 0.1f, 100.0f);
		// Camera matrix
		glm::mat4 view = glm::lookAt(
				glm::vec3(4,3,3), // Camera is at (4,3,3)
				glm::vec3(0,0,0), // Camera looks at (0,0,0)
				glm::vec3(0,1,0) // Head is up [ (0,-1,0) would be upside-down)
		);
		// Model matrix (identity matrix -> model will be at the origin)
		glm::mat4 model = glm::mat4(1.0f);
		// Move Model
		glm::mat4 translateMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(movementPosX, 0.0f, 0.0f));
		if ( movingForward == true ) {
			if ( movementPosX <= 1.0 ) {
				movementPosX += 0.01;
			} else {
				movingForward = false;
			}
		} else {
			if ( movementPosX >= -1.0 ) {
				movementPosX -= 0.01;
			} else {
				movingForward = true;
			}
		}
		model = translateMatrix * model;
		// Rotate model
		model = glm::rotate(model, myAngle, glm::vec3(0,1,0));
		if ( myAngle < 6.28318f && rotations > 0) {
			myAngle += 0.03f;
		} else if ( rotations > 0 ){
			rotations--;
			myAngle = 0.0f;
		}

		// ModelViewProjection-Matrix
		glm::mat4 mvp = projection * view * model;
		// Send matrix to the shader
		GLuint MatrixID = glGetUniformLocation(shader.getShaderProgramID(), "mvp");
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

		// TO BE EXPORTED INTO A MESH CLASS
		// DRAWING A TRIANGLE
		//#######################################################

		// First attribute buffer: vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		// Second attribute buffer: color
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

		// Draw Cube
		glDrawArrays(GL_TRIANGLES, 0, 12*3); // Starting from vertex 0; 3 vertices

		// Draw Platform under Cube
		mvp = projection * view;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
		glDrawArrays(GL_TRIANGLES, 36, 6);
		glDisableVertexAttribArray(0);

		//#######################################################

		m_window.Update();
	}

	return 0;
}


