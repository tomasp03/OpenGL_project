#include "Cube.h"

Cube::Cube(const char* shader)
	: 
	mColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)),
	mVertices(NULL),
	mVerticesLength(0),
	mIndices(NULL),
	mIndicesLength(0),
	mShader(new ShaderClass(shader)),
	mVAO(new VertexArray()),
	mVertexBuffer(NULL),
	mIndicesBuffer(NULL)
{
}

glm::vec4 Cube::GetColor()
{
	return mColor;
}

void Cube::SetColor(glm::vec4 color)
{
	mColor = color;
}