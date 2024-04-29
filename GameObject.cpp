#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "GameObject.h"


void GameObject::render() {
	GLuint VAO, VBO;
	GLfloat Vertices[5];
};

void GameObject::draw() {
	const float radius = 0.025f;
	int location[2];
	location[0] = 0;
	location[1] = 1;
	GLfloat ballVertices[360 * 3];
};