/*
 * window.h
 *
 *  Created on: 18.04.2015
 *      Author: robert
 */

#ifndef WINDOW_H_
#define WINDOW_H_

#include <String>
#include <GL/glew.h>
#include <glfw/glfw3.h>
//tmp includes
//#include <iostream>

class Window {
public:
	Window(int width, int height, std::string title);
	virtual ~Window();

	void Clear(float r, float g, float b, float a);
	bool IsClosed();
	void Update();
private:
	GLFWwindow* m_window;
	bool m_isClosed;
};

#endif /* WINDOW_H_ */
