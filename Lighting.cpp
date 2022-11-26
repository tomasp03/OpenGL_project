#include "Lighting.h"

Lighting::Lighting(GLfloat* vertices, int verticesLength, GLuint* indices, int indicesLength, const char* shader) : Cube(shader)
{
	mVerticesLength = verticesLength;
	mIndicesLength = indicesLength;
	mVertices = vertices;
	mIndices = indices;

	mVAO->Bind();
	mVertexBuffer = new VBO(mVertices, mVerticesLength);
	mIndicesBuffer = new EBO(mIndices, mIndicesLength);
	mVAO->LinkBuffer(*mVertexBuffer, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	mVAO->Unbind();
	mVertexBuffer->Unbind();
	mIndicesBuffer->Unbind();
	mShader->Activate();
	Uniforms();
}

Lighting::~Lighting()
{
	mVAO->~VertexArray();
	mVertexBuffer->Delete();
	mIndicesBuffer->Delete();
	mShader->~ShaderClass();
}

void Lighting::Uniforms()
{
	glUniform4fv(glGetUniformLocation(mShader->ID, "u_lightColor"), 1, glm::value_ptr(mColor));

}

void Lighting::Draw(Camera camera)
{
	mShader->Activate();
	Uniforms();
	glUniform1f(glGetUniformLocation(mShader->ID, "u_time"), (float)glfwGetTime());
	mVAO->Bind();
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, mPos);
	glUniformMatrix4fv(glGetUniformLocation(mShader->ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
	camera.Matrix(0.1f, 100.0f, *mShader, "camMatrix");
	glDrawElements(GL_TRIANGLES, mIndicesLength / sizeof(GLuint), GL_UNSIGNED_INT, 0);
	mVAO->Unbind();
}

void Lighting::Movement()
{
	//dont forget to make the change for the uniform
}