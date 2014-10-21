#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>
#include "Entity.h"
#include "StatSprite.h"
#include "BoneSprite.h"

Entity::Entity() {
	// Temporary, initializes the player
	sprite = new BoneSprite();
	deltaX = deltaY = 0.;
	posX = 40.;
	posY = 120.;
	bbWidth = 10.;
	bbHeight = 100.;
	gravity = 0.;
	fixed = false;
}

Entity::Entity(string t, float x, float y, float w, float h) {
	sprite = new StatSprite(t, w, h);
	posX = x;
	posY = y;
	bbWidth = w;
	bbHeight = h;
	gravity = 0.;
	fixed = true;
}

Entity::~Entity() {
	delete sprite;
}

bool Entity::ecollides(const Entity * e) {
	if (e == this) return false;
	if (e->posX >= posX + bbWidth || posX >= e->posX + e->bbWidth) return false;
	if (e->posY >= posY + bbHeight || posY >= e->posY + e->bbHeight) return false;
	return true;
}

bool Entity::lcollides(const Level * l) {
	for (int i = 0; i < l->entities.size(); i++) {
		if (ecollides(l->entities[i])) return true;
	}
	return false;
}

bool Entity::translate(float dx, float dy, const Level * l) {
	posX += dx;
	posY += dy;
	if (lcollides(l)) {
		posX -= dx;
		posY -= dy;
		return false;
	}
	return true;
}

void Entity::update(const Level * l) {
	// update gravity
	if (!fixed) {
		gravity -= .0001;
		if (!translate(0, gravity, l)) {
			gravity = 0.;
		}
	}

	// update arbitrary deltas
	translate(deltaX, deltaY, l);
}

void Entity::render(glm::mat4 view) {
	sprite->render(view,posX,posY);
}

