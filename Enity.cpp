#include "Entity.h"

Entity::Entity()
	:mPos(glm::vec3(0.0f, 0.0f, 0.0f))
{
}

glm::vec3 Entity::GetPos()
{
	return mPos;
}

void Entity::SetPos(glm::vec3 position)
{
	mPos = position;
}