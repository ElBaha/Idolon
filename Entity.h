#ifndef ENTITY_H
#define ENTITY_H

#include "Sprite.h"

class Entity
{
	Sprite * sprite;
	float posX, posY;

public:
	Entity();
	~Entity();

	void translate(float dx, float dy);
	void render(glm::mat4 view);
};

#endif
