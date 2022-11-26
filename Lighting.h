#pragma once

#include "Camera.h"
#include "Cube.h"

class Lighting : public Cube
{
public:
	Lighting(GLfloat* vertices, int verticesLength, GLuint* indices, int indicesLength, const char* shader);
	~Lighting();
	void Uniforms();
	void Draw(Camera camera);
	void Movement();
};

