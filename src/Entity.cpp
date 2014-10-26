#include <stdlib.h>
#include "Entity.h"
#include "StatSprite.h"
#include "BoneSprite.h"
#include "TweakableMechanics.h"

Entity::Entity() {
	// Temporary, initializes the player
	sprite = new BoneSprite();
	delta.x = delta.y = 0.;
	accel.x = accel.y = 0.;
	pos.x = 40.;
	pos.y = 120.;
	box.x = 6.;
	box.y = 20.;
	fixed = false;
	collidable=true;
	use=NULL;
	heldObject=NULL;
}

Entity::Entity(string t, float x, float y, float w, float h) {
	sprite = new StatSprite(t, w, h);
	delta.x = delta.y = 0.;
	accel.x = accel.y = 0.;
	pos.x = x;
	pos.y = y;
	box.x = w;
	box.y = h;
	fixed = false;//true;
	collidable=true;
	use=NULL;
	heldObject=NULL;
}

Entity::~Entity() {
	delete sprite;
}

void Entity::collides(const Entity * e) {
	if (e == this || !e->collidable) return;
	if (e->pos.x >= pos.x + box.x || pos.x >= e->pos.x + e->box.x) return;
	if (e->pos.y >= pos.y + box.y || pos.y >= e->pos.y + e->box.y) return;

	// have a collision, adjust for it
	float dx1 = -(e->pos.x + e->box.x) + pos.x;
	float dx2 = -e->pos.x + (pos.x + box.x);
	float dy1 = -(e->pos.y + e->box.y) + pos.y;
	float dy2 = -e->pos.y + (pos.y + box.y);

	float dx = abs(dx1) < abs(dx2) ? dx1 : dx2;
	float dy = abs(dy1) < abs(dy2) ? dy1 : dy2;

	if (abs(dx) < abs(dy)-10 || dy>0) {
		pos.x -= dx;
		if (dx < 0 && delta.x < 0) delta.x = 0.;
		if (dx > 0 && delta.x > 0) delta.x = 0.;
	} else {
		pos.y -= dy;
		delta.y = 0.;
	}

	// friction
	delta.x *= friction_x;
	delta.y *= friction_y;
}

bool Entity::canUse(Entity* e){
	if(!use)
		return false;

	if (e->pos.x >= pos.x + box.x || pos.x >= e->pos.x + e->box.x*2) return false;
	if (e->pos.y >= pos.y + box.y || pos.y >= e->pos.y + e->box.y) return false;

	return true;
}

void Entity::update(const Level * l) {
	// adjust for gravity
	if (!fixed) {
		delta.y -= gravity_acceleration;
	}
	
	//adjust held object
	if(heldObject!=NULL){
		heldObject->pos.x=(box.x+pos.x)+1;
		for (map<std::string, Entity *>::const_iterator it = l->entities.begin(); it != l->entities.end(); ++it)
			heldObject->collides(it->second);
		
		if(abs(heldObject->pos.x-pos.x)<box.x)
			heldObject=NULL;
	}
	// update position
	delta.x += accel.x;
	delta.y += accel.y;

	if ( delta.x >  max_delta_x) delta.x =  max_delta_x;
	if (-delta.x < -max_delta_x) delta.x = -max_delta_x;
	if ( delta.y >  max_delta_y) delta.y =  max_delta_y;
	if (-delta.y < -max_delta_y) delta.y = -max_delta_y;

	pos.x += delta.x;
	pos.y += delta.y;

	if(pos.y<0){
	    pos.y=0;
	    delta.y=0;
	    delta.x *= friction_x;
	}

	// don't bother to check collision if we don't move
	if (delta.x || delta.y) {
		// adjust for collisions
		for (map<std::string, Entity *>::const_iterator it = l->entities.begin(); it != l->entities.end(); ++it) {
			collides(it->second);
		}
	}
}

void Entity::setAnim(int s){
	sprite->setState(s);
}

void Entity::render(glm::mat4 view) {
	sprite->render(view, pos.x, pos.y);
}

