#include "TexturedCube.h"

TexturedCube::TexturedCube(GLfloat* vertices, int verticesLength, const char* shader, const char* texture) : Cube(shader)
{
	mVerticesLength = verticesLength;
	mVertices = vertices;

	mVAO->Bind();
	mVertexBuffer = new VBO(mVertices, mVerticesLength);
	mTexture = new Texture(texture, "main", 0, GL_RGB, GL_UNSIGNED_BYTE);
	mVAO->LinkBuffer(*mVertexBuffer, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	mVAO->LinkBuffer(*mVertexBuffer, 1, 2, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	mVAO->LinkBuffer(*mVertexBuffer, 2, 3, GL_FLOAT, 8 * sizeof(float), (void*)(5 * sizeof(float)));
	mVAO->Unbind();
	mVertexBuffer->Unbind();
	mIndicesBuffer->Unbind();
	mShader->Activate();
	mTexture->texUnit(*mShader, "tex0", 0);
}

TexturedCube::~TexturedCube()
{
	mVAO->~VertexArray();
	mVertexBuffer->Delete();
	mTexture->Delete();
	mShader->~ShaderClass();
}

void TexturedCube::Draw(Camera camera)
{
	mShader->Activate();
	mVAO->Bind();
	camera.Matrix(0.1f, 100.0f, *mShader, "camMatrix");
	mTexture->Bind();
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, mPos);
	glUniformMatrix4fv(glGetUniformLocation(mShader->ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
	camera.Matrix(0.1f, 100.0f, *mShader, "camMatrix");
	glDrawArrays(GL_TRIANGLES, 0, 36);
	mVAO->Unbind();
}

void TexturedCube::Light(glm::vec3 Pos, glm::vec4 Color)
{
	glUniform3fv(glGetUniformLocation(mShader->ID, "u_lightPos"), 1, glm::value_ptr(Pos));
	glUniform4fv(glGetUniformLocation(mShader->ID, "u_lightColor"), 1, glm::value_ptr(Color));
}
