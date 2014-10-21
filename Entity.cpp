#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>
#include "Entity.h"
#include "BoneSprite.h"

Entity::Entity() {
	sprite = new BoneSprite();
	posX = posY = 0.;
}

Entity::~Entity() {
	delete sprite;
}

void Entity::translate(float dx, float dy) {
	posX += dx;
	posY += dy;
}

void Entity::render(glm::mat4 view) {
	sprite->render(view,posX,posY);
}
