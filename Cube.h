#pragma once
#include "Entity.h"
#include "ShaderClass.h"
#include "VertexArray.h"
#include "VBO.h"
#include "EBO.h"


class Cube : public Entity
{
protected:
	glm::vec4 mColor;
	GLfloat* mVertices;
	int mVerticesLength;
	GLuint* mIndices;
	int mIndicesLength;
	ShaderClass* mShader;
	VertexArray* mVAO;
	VBO* mVertexBuffer;
	EBO* mIndicesBuffer;
public:
	Cube(const char* shader);
	glm::vec4 GetColor();
	void SetColor(glm::vec4 color);
};