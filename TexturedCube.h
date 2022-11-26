#pragma once

#include "Cube.h"
#include "Texture.h"
#include "Camera.h"

class TexturedCube : public Cube
{
protected:
	Texture* mTexture;
	
public:
	TexturedCube(GLfloat* vertices, int verticesLength, const char* shader, const char* texture);
	~TexturedCube();
	void Draw(Camera camera);
	void Light(glm::vec3 Pos, glm::vec4 Color);
};



