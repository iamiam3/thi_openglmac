/*
 * shader.cpp
 *
 *  Created on: 18.04.2015
 *      Author: robert
 */

#include "shader.h"


Shader::Shader(const std::string& fileName) {
	// Create program
	m_program = glCreateProgram();
	// Create shaders
	m_shaders[0] = CreateShader(LoadShader(fileName + ".vertexshader"), GL_VERTEX_SHADER);
	m_shaders[1] = CreateShader(LoadShader(fileName + ".fragmentshader"), GL_FRAGMENT_SHADER);

	// Link the program
	for (unsigned int i = 0; i < NUM_SHADERS; i++) {
		glAttachShader(m_program, m_shaders[i]);
	}
	glLinkProgram(m_program);

	// Check if linking worked
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Error: Program linking failed");

	// Check if program is valid
	// Can only be done after vertex array object is bound
	// TODO Add the validation to the mesh (After the Vertex Array Object is bound)
	//glValidateProgram(m_program);
	//CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Program is invalid");
}

Shader::~Shader() {
	for (unsigned int i = 0; i < NUM_SHADERS; i++) {
		// Detach shader from program
		glDetachShader(m_program, m_shaders[i]);
		// Delete shader
		glDeleteShader(m_shaders[i]);
	}
	// Delete program
	glDeleteProgram(m_program);
}


void Shader::Bind() {
	glUseProgram(m_program);
}

void Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage) {
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram) {
		glGetProgramiv(shader, flag, &success);
	} else {
		glGetShaderiv(shader, flag, &success);
	}

	if (success == GL_FALSE) {
		if(isProgram) {
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		} else {
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);
		}
		// TODO Error Handling (Shader or program not compiled correctly | check errorMessage}
		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}

std::string Shader::LoadShader(const std::string& fileName) {
	// Open filestream
	std::ifstream file;
	file.open((fileName).c_str());

	std::string output;
	std::string line;

	// Open was successful
	if(file.is_open()) {
		// while the file stream is valid
		while(file.good()) {
			getline(file,line);
			output.append(line + "\n");
		}
	// Open wasn't successful
	} else {
		// TODO Error Handling (Filestream error)
		std::cerr << "Unable to load shader: " << fileName << std::endl;
	}

	return output;
}

GLuint Shader::CreateShader(const std::string& text, GLenum shaderType) {
	// Create shader
	GLuint shader = glCreateShader(shaderType);

	if ( shader == 0 ) {
		// TODO Error Handling (Shader creation failed)
		std::cerr << "Shader creation failed" << std::endl;
	}

	// Compile shader
	const GLchar* shaderSourceStrings[1];
	GLint shaderSourceStringLengths[1];
	shaderSourceStrings[0] = text.c_str();
	shaderSourceStringLengths[0] = text.length();
	glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
	glCompileShader(shader);

	// Check if shader was compiled correctly
	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader compilation failed");

	// return compiled shader
	return shader;
}








