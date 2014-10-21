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
	float bbWidth, bbHeight;
	float gravity;

protected:
	bool ecollides(const Entity *);
	bool lcollides(const Level *);

public:
	Entity();
	Entity(string t, float x, float y, float w, float h);
	~Entity();

	bool translate(float dx, float dy, const Level *);
	void update(const Level *);
	void render(glm::mat4 view);

	bool fixed;
};

#endif
