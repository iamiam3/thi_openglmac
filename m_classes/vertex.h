/*
 * vertex.h
 *
 *  Created on: 18.04.2015
 *      Author: robert
 */

#ifndef VERTEX_H_
#define VERTEX_H_

#include <glm/glm.hpp>

class Vertex {
public:
	Vertex(const glm::vec3& pos) { this->pos = pos; }
private:
	glm::vec3 pos;
};

#endif /* VERTEX_H_ */
