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
#include "m_classes/controller.h"
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

	Object logoObject("./res/logo.obj", glm::vec3(0,1,0));
	logoObject.setColor(0.0f, 0.0f, 0.9f);
	logoObject.scaleTo(glm::vec3(0.3f,0.3f,0.3f));

//	Object treeObject("./res/tree.obj", glm::vec3(0,1,0));
//	treeObject.setColor(1.0f,1.0f, 1.0f);

	Mesh m_mesh(m_shader.getShaderProgramID());

	Controller m_controller(&m_window, &m_mesh);

	m_mesh.addObject(&logoObject);
//	m_mesh.addObject(&treeObject);

	m_mesh.addGrid();

	/*m_mesh.addObject(&m_triangleObject);
	m_mesh.addObject(&m_triangleObject2);*/

	double m_time = glfwGetTime();

	while ( !m_window.IsClosed() ) {
		//m_window.Clear(0.0f, 0.15f, 0.3f, 1.0f); // blue
		//m_window.Clear(1.0f, 1.0f, 1.0f, 1.0f); // white
		m_window.Clear(0.45f, 0.45f, 0.45f, 1.0f); // grey

		m_shader.Bind();

		/*m_triangleObject.rotateBy(1, glm::vec3(0,1,0));
		m_triangleObject2.rotateBy(1, glm::vec3(0,1,0));*/
		logoObject.rotateBy(1, glm::vec3(0,1,0));
		if (glfwGetKey(m_window.getWindowPointer(), GLFW_KEY_H) == GLFW_PRESS) {
			logoObject.scaleBy(glm::vec3(1.01f, 1.01f, 1.01f));
		}
		if (glfwGetKey(m_window.getWindowPointer(), GLFW_KEY_J) == GLFW_PRESS) {
			logoObject.scaleBy(glm::vec3(0.99f, 0.99f, 0.99f));
		}

		m_mesh.drawMesh();

		m_window.Update();

		m_controller.checkInput();

		m_controller.setDeltaTime(float(glfwGetTime()-m_time));

//		std::cout << int(1/(glfwGetTime()-m_time)) << std::endl;

		m_time = glfwGetTime();
	}



	return 0;
}


