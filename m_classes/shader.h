/*
 * shader.h
 *
 *  Created on: 18.04.2015
 *      Author: robert
 */

#ifndef SHADER_H_
#define SHADER_H_

#include <string>
#include <GL/glew.h>
#include <fstream>
#include <iostream>

class Shader {
public:
	Shader(const std::string& fileName);
	virtual ~Shader();
	GLuint getShaderProgramID() { return m_program; }

	void Bind();
private:
	void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	std::string LoadShader(const std::string& fileName);
	GLuint CreateShader(const std::string& text, GLenum shaderType);

	static const unsigned int NUM_SHADERS = 2;
	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
};

#endif /* SHADER_H_ */
