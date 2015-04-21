/*
 * main.cpp
 *
 *  Created on: 18.04.2015
 *      Author: John Robert Westman
 */

#include <iostream>
#include "m_classes/window.h"
#include "m_classes/shader.h"
#include "m_classes/object.h"
#include "m_classes/mesh.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/transform.hpp>

int main(int argc, char **argv) {

	Window m_window(800,600,"THI - Seminar - OpenGL Beispiel");

	Shader m_shader("./res/basicShader");

	/*std::vector<glm::vec3> m_triangleVertices;
	m_triangleVertices.push_back(glm::vec3(-0.5f, 0.0f, 0.0f));
	m_triangleVertices.push_back(glm::vec3(-0.5f, 1.0f, 0.0f));
	m_triangleVertices.push_back(glm::vec3(0.5f, 1.0f, 0.0f));
	Object m_triangleObject(m_triangleVertices, glm::vec3(0,0,0), GL_TRIANGLES);

	std::vector<glm::vec3> m_triangleVertices2;
	m_triangleVertices2.push_back(glm::vec3(0.5f, 1.0f, 0.0f));
	m_triangleVertices2.push_back(glm::vec3(0.5f, 0.0f, 0.0f));
	m_triangleVertices2.push_back(glm::vec3(-0.5f, 0.0f, 0.0f));
	Object m_triangleObject2(m_triangleVertices2, glm::vec3(0,0,0), GL_TRIANGLES);*/

	Object loadedObject("./res/logo.obj", glm::vec3(0,1,0));
	loadedObject.setColor(0.0f, 0.0f, 0.9f);
	loadedObject.scaleBy(glm::vec3(0.2f,0.2f,0.2f));

	Mesh m_mesh(m_shader.getShaderProgramID());

	m_mesh.addObject(&loadedObject);

	m_mesh.addGrid();

	/*m_mesh.addObject(&m_triangleObject);
	m_mesh.addObject(&m_triangleObject2);*/

	while ( !m_window.IsClosed() ) {
		//m_window.Clear(0.0f, 0.15f, 0.3f, 1.0f); // blue
		//m_window.Clear(1.0f, 1.0f, 1.0f, 1.0f); // white
		m_window.Clear(0.45f, 0.45f, 0.45f, 1.0f); // grey

		m_shader.Bind();

		/*m_triangleObject.rotateBy(1, glm::vec3(0,1,0));
		m_triangleObject2.rotateBy(1, glm::vec3(0,1,0));*/
		loadedObject.rotateBy(1, glm::vec3(0,1,0));

		m_mesh.drawMesh();

		m_window.Update();
	}

	return 0;
}


