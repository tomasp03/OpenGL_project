#pragma once
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>

class Entity
{
protected:
	glm::vec3 mPos;
	
public:
	Entity();
	glm::vec3 GetPos();
	void SetPos(glm::vec3 position);
};


