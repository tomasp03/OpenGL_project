#pragma once
#include "BufferClass.h"

class EBO : public BufferClass
{
public:
	EBO(GLuint* array, GLsizeiptr size);
	void Bind();
	void Unbind();
	void Data(GLuint* array);
};