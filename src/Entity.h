#ifndef ENTITY_H
#define ENTITY_H

class Entity;

#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>
#include "Level.h"
#include "Sprite.h"
#include "StatSprite.h"

class Entity
{
    public:
	Sprite * sprite;
	float angle;
	glm::vec2 pos, delta, box;

protected:
	void collides(const Entity *);

public:
	Entity();
	Entity(string t, float x, float y, float w, float h);
	~Entity();

	void update(const Level *);
	void render(glm::mat4 view);
	void setAnim(int s);

	bool fixed;
	glm::vec2 accel;
};

#endif
