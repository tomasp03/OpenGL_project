#include "EBO.h"

EBO::EBO(GLuint* array, GLsizeiptr size)
{
	mSize = size;
	glGenBuffers(1, &mID);
	Bind();
	Data(array);
}

void EBO::Data(GLuint* array)
{
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mSize, array, GL_DYNAMIC_DRAW);
}

void EBO::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mID);
}

void EBO::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}