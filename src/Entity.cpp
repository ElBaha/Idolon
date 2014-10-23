#define GLM_FORCE_RADIANS
#include <stdlib.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Entity.h"
#include "StatSprite.h"
#include "BoneSprite.h"
#include "TweakableMechanics.h"

Entity::Entity() {
	// Temporary, initializes the player
	sprite = new BoneSprite();
	deltaX = deltaY = 0.;
	accelX = accelY = 0.;
	posX = 40.;
	posY = 120.;
	bbRot = 0.;
	bbWidth = 10.;
	bbHeight = 100.;
	fixed = false;
}

Entity::Entity(string t, float x, float y, float w, float h, float r) {
	sprite = new StatSprite(t, w, h);
	deltaX = deltaY = 0.;
	accelX = accelY = 0.;
	posX = x;
	posY = y;
	bbWidth = w;
	bbHeight = h;
	bbRot = r;
	fixed = true;
}

Entity::~Entity() {
	delete sprite;
}

void Entity::collides(const Entity * e) {
	if (e == this) return;
	if (e->posX >= posX + bbWidth || posX >= e->posX + e->bbWidth) return;
	if (e->posY >= posY + bbHeight || posY >= e->posY + e->bbHeight) return;

	// have a collision, adjust for it
	float dx1 = -(e->posX + e->bbWidth) + posX;
	float dx2 = -e->posX + (e->posX + e->bbWidth);
	float dy1 = -(e->posY + e->bbHeight) + posY;
	float dy2 = -e->posY + (e->posY + e->bbHeight);

	float dx = abs(dx1) < abs(dx2) ? dx1 : dx2;
	float dy = abs(dy1) < abs(dy2) ? dy1 : dy2;

	if (abs(dx) < abs(dy)) {
		posX -= dx;
		if (dx < 0 && deltaX < 0) deltaX = 0.;
		if (dx > 0 && deltaX > 0) deltaX = 0.;
	} else {
		posY -= dy;
		deltaY = 0.;
	}

	// friction
	deltaX *= friction_x;
	deltaY *= friction_y;
}

void Entity::update(const Level * l) {
	// adjust for gravity
	if (!fixed) {
		deltaY -= gravity_acceleration;
	}

	// update position
	deltaX += accelX;
	deltaY += accelY;

	if ( deltaX >  max_delta_x) deltaX =  max_delta_x;
	if (-deltaX < -max_delta_x) deltaX = -max_delta_x;
	if ( deltaY >  max_delta_y) deltaY =  max_delta_y;
	if (-deltaY < -max_delta_y) deltaY = -max_delta_y;

	posX += deltaX;
	posY += deltaY;

	// don't bother to check collision if we don't move
	if (deltaX || deltaY) {
		// adjust for collisions
		for (int i = 0; i < l->entities.size(); i++) {
			collides(l->entities[i]);
		}
	}
}

void Entity::render(glm::mat4 view) {
	sprite->render(view, posX, posY);
}

