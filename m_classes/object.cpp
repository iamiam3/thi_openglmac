/*
 * object.cpp
 *
 *  Created on: 19.04.2015
 *      Author: robert
 */

#include "object.h"

Object::Object(std::vector<glm::vec3> p_vertices, glm::vec3 p_position) {
	// Reset matrices
	mc_objectMatrix= glm::mat4(1.0f);
	mc_translationMatrix = glm::mat4(1.0f);
	mc_rotationMatrix = glm::mat4(1.0f);
	mc_scaleMatrix = glm::mat4(1.0f);

	// Set vertices
	mc_vertices = p_vertices;
	// Move to position
	moveTo(p_position);
}

Object::~Object() {

}

void Object::moveBy(glm::vec3 p_position) {
	mc_translationMatrix = glm::translate(mc_translationMatrix, p_position);
	updateTranslationMatrix();
}

void Object::moveTo(glm::vec3 p_position) {
	mc_translationMatrix = glm::translate(glm::mat4(1.0f), p_position);
	updateTranslationMatrix();
}

void Object::updateTranslationMatrix() {
	mc_objectMatrix = mc_rotationMatrix * mc_translationMatrix * mc_scaleMatrix;
}

std::vector<glm::vec3> Object::getVertices() {
	return mc_vertices;
}
