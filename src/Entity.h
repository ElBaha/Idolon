#ifndef ENTITY_H
#define ENTITY_H

class Entity;

#include "Level.h"
#include "Sprite.h"
#include "StatSprite.h"

class Entity
{
	Sprite * sprite;
	float posX, posY;
	float bbRot;
	float bbWidth, bbHeight;
	float gravity;

protected:
	void collides(const Entity *);

public:
	Entity();
	Entity(string t, float x, float y, float w, float h, float r);
	~Entity();

	void update(const Level *);
	void render(glm::mat4 view);

	bool fixed;
	float accelX, accelY;
	float deltaX, deltaY;
};

#endif
