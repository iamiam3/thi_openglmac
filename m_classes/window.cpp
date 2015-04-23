/*
 * window.cpp
 *
 *  Created on: 18.04.2015
 *      Author: robert
 */

#include "window.h"

Window::Window(int width, int height, std::string title) {
	// Initialise GLFW
	if ( !glfwInit() ) {
		// TODO Error Handling (GLFW failed to initialize)
	}

	// GLFW window general settings
	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	// GLFW window version settings
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // OpenGL V3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open window
	m_window = glfwCreateWindow( width, height, title.c_str(), NULL, NULL);
	if ( m_window == NULL ) {
		// TODO Error Handling (GLFW window failed to open)
		glfwTerminate();
	}
	// Create OpenGL context
	glfwMakeContextCurrent(m_window);
	glewExperimental = true; // (needed in core profile)
	// Initialise GLEW
	if ( glewInit() != GLEW_OK ) {
		// TODO Error Handling (GLEW failed to initialise)
	}
	m_isClosed = false;

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it is closer to the camera then the former one
	glDepthFunc(GL_LESS);
}

Window::~Window() {
	// Close GL context and any other GLFW resource
	glfwTerminate();
}

void Window::Clear(float r, float g, float b, float a) {
	glClearColor(r, g, b, b);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool Window::IsClosed() {
	return m_isClosed;
}

void Window::Update() {
	// Swap Buffers
	glfwSwapBuffers(m_window);
	// Processes poll events in the event queue
	glfwPollEvents();

	// if ESC pressed close
	if ( glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS && m_isClosed == false ) {
		m_isClosed = true;
	}
	// If window was closed set isClosed to true
	if ( glfwWindowShouldClose(m_window) == true && m_isClosed == false ) {
		m_isClosed = true;
	}
}

GLFWwindow* Window::getWindowPointer() {
	return m_window;
}
