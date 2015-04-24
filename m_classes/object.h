/*
 * object.h
 *
 *  Created on: 19.04.2015
 *      Author: robert
 */

#ifndef OBJECT_H_
#define OBJECT_H_

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <math.h>
#include <String>
#include <iostream>

class Object {
public:
	Object(std::vector<glm::vec3> p_vertices, glm::vec3 p_position, GLenum p_vertexType);
	Object(const std::string p_fileName, glm::vec3 p_position);
	virtual ~Object();

	void moveBy(glm::vec3 p_position);
	void moveTo(glm::vec3 p_position);
	void scaleTo(glm::vec3 p_scale);
	void scaleBy(glm::vec3 p_scale);
	void rotateBy(int p_degrees, glm::vec3 p_rotationAxis);

	void setColor(float p_r, float p_g, float p_b);

	GLenum getVertexType();
	std::vector<glm::vec3> getVertices();
	glm::mat4 getTransformationMatrix();
	GLfloat* getColor();
private:
	std::vector<glm::vec3> mc_vertices;
	GLfloat mc_color[3];
	glm::mat4 mc_transformationMatrix;
	glm::mat4 mc_translationMatrix;
	glm::mat4 mc_rotationMatrix;
	glm::mat4 mc_scaleMatrix;
	GLenum mc_vertexType;
	bool mc_hasMaterials;

	void updateTranslationMatrix();
	void loadVerticesFromFile(const std::string p_fileName);
};

#endif /* OBJECT_H_ */
