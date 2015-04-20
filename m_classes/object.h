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
#include <vector>

class Object {
public:
	Object(std::vector<glm::vec3> p_vertices, glm::vec3 p_position);
	virtual ~Object();

	void moveBy(glm::vec3 p_position);
	void moveTo(glm::vec3 p_position);

	std::vector<glm::vec3> getVertices();
private:
	std::vector<glm::vec3> mc_vertices;
	glm::mat4 mc_objectMatrix;
	glm::mat4 mc_translationMatrix;
	glm::mat4 mc_rotationMatrix;
	glm::mat4 mc_scaleMatrix;

	void updateTranslationMatrix();
};

#endif /* OBJECT_H_ */
