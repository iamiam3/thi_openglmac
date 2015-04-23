/*
 * object.cpp
 *
 *  Created on: 19.04.2015
 *      Author: robert
 */

#include "object.h"

Object::Object(std::vector<glm::vec3> p_vertices, glm::vec3 p_position, GLenum p_vertexType) {
	// Default color black
	setColor(0.0f,0.0f,0.0f);
	// Reset matrices
	mc_transformationMatrix= glm::mat4(1.0f);
	mc_translationMatrix = glm::mat4(1.0f);
	mc_rotationMatrix = glm::mat4(1.0f);
	mc_scaleMatrix = glm::mat4(1.0f);
	mc_hasMaterials = false;

	// Set vertices
	mc_vertices = p_vertices;
	// Move to position
	moveTo(p_position);

	// Set VertexType
	mc_vertexType = p_vertexType;
}

Object::Object(const std::string p_fileName, glm::vec3 p_position) {
	// Default color black
	setColor(0.0f,0.0f,0.0f);
	// Reset matrices
	mc_transformationMatrix= glm::mat4(1.0f);
	mc_translationMatrix = glm::mat4(1.0f);
	mc_rotationMatrix = glm::mat4(1.0f);
	mc_scaleMatrix = glm::mat4(1.0f);
	mc_hasMaterials = false;

	// Load vertices
	loadVerticesFromFile(p_fileName);
	/*std::vector<glm::vec3> out_vertices, out_normals;
	std::vector<glm::vec2> out_uvs;
	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> tmp_vertices;
	std::vector<glm::vec2> tmp_uvs;
	std::vector<glm::vec3> tmp_normals;
	FILE * file = fopen(p_fileName.c_str(), "r");
	if ( file == NULL ) {
		std::cerr << "Couldn't open file" << std::endl;
		// TODO Error Handling (couldn't object file)
	}
	while ( true ) {
		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF) {
			break; // EOF = End Of File. Quit the loop
		}
		// else : parse lineHeader
		if ( strcmp(lineHeader, "v") == 0) {
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			tmp_vertices.push_back(vertex);
		} else if (strcmp (lineHeader, "vt" ) == 0 ) {
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			tmp_uvs.push_back(uv);
		} else if (strcmp(lineHeader, "vn") == 0) {
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			tmp_normals.push_back(normal);
		} else if (strcmp(lineHeader, "f") == 0 ) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
			if (matches != 9) {
				std::cerr << "File can't be read by our simple parser." << std::endl;
				// TODO Error Handling (parsing error while leading object file)
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices    .push_back(uvIndex[0]);
			uvIndices    .push_back(uvIndex[1]);
			uvIndices    .push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
	}
	for (unsigned int i=0; i<vertexIndices.size(); i++) {
		unsigned int vertexIndex = vertexIndices[i];
		glm::vec3 vertex = tmp_vertices[vertexIndex-1];
		mc_vertices.push_back(vertex);
	}
	for (unsigned int i=0; i<uvIndices.size(); i++) {
		unsigned int uvIndex = uvIndices[i];
		glm::vec2 uv = tmp_uvs[uvIndex-1];
		out_uvs.push_back(uv);
	}
	for (unsigned int i=0; i<normalIndices.size(); i++) {
		unsigned int normalIndex = normalIndices[i];
		glm::vec3 normal = tmp_normals[normalIndex-1];
		out_normals.push_back(normal);
	}*/

	// Move to position
	moveTo(p_position);

	// Set VertexType
	mc_vertexType = GL_TRIANGLES;
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

glm::mat4 Object::getTransformationMatrix() {
	return mc_transformationMatrix;
}

GLenum Object::getVertexType() {
	return mc_vertexType;
}

void Object::updateTranslationMatrix() {
	mc_transformationMatrix = mc_rotationMatrix * mc_translationMatrix * mc_scaleMatrix;
}

std::vector<glm::vec3> Object::getVertices() {
	return mc_vertices;
}

void Object::scaleBy(glm::vec3 p_scale) {
	mc_scaleMatrix = glm::scale(p_scale);
	updateTranslationMatrix();
}

void Object::rotateBy(int p_degrees, glm::vec3 p_rotationAxis) {
	// degrees to rad
	float m_radDegrees = p_degrees * M_PI / 180;
	mc_rotationMatrix = glm::rotate(mc_rotationMatrix, m_radDegrees, p_rotationAxis);
	updateTranslationMatrix();
}

GLfloat* Object::getColor() {
	return mc_color;
}

void Object::setColor(float p_r, float p_g, float p_b) {
	mc_color[0] = p_r;
	mc_color[1] = p_g;
	mc_color[2] = p_b;
}

void Object::loadVerticesFromFile(const std::string p_fileName) {
	// Load vertices
	std::vector<glm::vec3> out_vertices, out_normals;
	std::vector<glm::vec2> out_uvs;
	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> tmp_vertices;
	std::vector<glm::vec2> tmp_uvs;
	std::vector<glm::vec3> tmp_normals;
	FILE * file = fopen(p_fileName.c_str(), "r");
	if ( file == NULL ) {
		std::cerr << "Couldn't open file" << std::endl;
		// TODO Error Handling (couldn't object file)
	}
	while ( true ) {
		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF) {
			break; // EOF = End Of File. Quit the loop
		}
		// else : parse lineHeader
		if ( strcmp(lineHeader, "v") == 0) {
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			tmp_vertices.push_back(vertex);
		} else if (strcmp (lineHeader, "vt" ) == 0 ) {
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			tmp_uvs.push_back(uv);
		} else if (strcmp(lineHeader, "vn") == 0) {
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			tmp_normals.push_back(normal);
		} else if (strcmp(lineHeader, "f") == 0 ) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
			if (matches != 9) {
				std::cerr << "File can't be read by our simple parser." << std::endl;
				// TODO Error Handling (parsing error while leading object file)
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices    .push_back(uvIndex[0]);
			uvIndices    .push_back(uvIndex[1]);
			uvIndices    .push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
	}
	for (unsigned int i=0; i<vertexIndices.size(); i++) {
		unsigned int vertexIndex = vertexIndices[i];
		glm::vec3 vertex = tmp_vertices[vertexIndex-1];
		mc_vertices.push_back(vertex);
	}
	for (unsigned int i=0; i<uvIndices.size(); i++) {
		unsigned int uvIndex = uvIndices[i];
		glm::vec2 uv = tmp_uvs[uvIndex-1];
		out_uvs.push_back(uv);
	}
	for (unsigned int i=0; i<normalIndices.size(); i++) {
		unsigned int normalIndex = normalIndices[i];
		glm::vec3 normal = tmp_normals[normalIndex-1];
		out_normals.push_back(normal);
	}
}
