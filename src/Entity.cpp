#include <stdlib.h>
#include <iostream>
#include "Entity.h"
#include "StatSprite.h"
#include "BoneSprite.h"
#include "TweakableMechanics.h"
#include "Rect.h"

Entity::Entity() {
	// Temporary, initializes the player
	sprite = new BoneSprite();
	delta.x = delta.y = 0.;
	accel.x = accel.y = 0.;
	rect.org().x = 40.;
	rect.org().y = 120.;
	rect.dim().x = 10.;
	rect.dim().y = 20.;
	fixed = false;
}

Entity::Entity(string t, float x, float y, float w, float h) {
	sprite = new StatSprite(t, w, h);
	delta.x = delta.y = 0.;
	accel.x = accel.y = 0.;
	rect.org().x = x;
	rect.org().y = y;
	rect.dim().x = w;
	rect.dim().y = h;
	fixed = true;
}

Entity::Entity(string t, Rect r) {
	sprite = new StatSprite(t, r.dim().x, r.dim().y);
	delta.x = delta.y = 0.;
	accel.x = accel.y = 0.;
	rect = r;
	fixed = true;
}

Entity::~Entity() {
	delete sprite;
}

void Entity::collides(const Entity * e) {
	if (e == this) return;
	
	HitRec rec = rect.testHit(e->rect);
	//std::cout<<"HIT INFO: "<<rec.hit<<" "<<rec.d.x<<" "<<rec.d.y<<std::endl;
	if(!rec.hit) return;

	// have a collision, adjust for it
	if(rec.hit&HIT_BOTTOM) {
		rect.org().y+=rec.d.y;
	}
	if(rec.hit&HIT_TOP) {
		rect.org().y-=rec.d.y;
	}
	if(rec.hit & (HIT_TOP|HIT_BOTTOM)) {
		delta.y=0;
		//std::cout<<"HIT VERTICALLY: "<<rec.d.y<<std::endl;
	}
	if(rec.hit&HIT_LEFT) {
		rect.org().x+=rec.d.x;
	}
	if(rec.hit&HIT_RIGHT) {
		rect.org().x-=rec.d.x;
	}
	if(rec.hit & (HIT_LEFT|HIT_RIGHT)) {
		delta.x=0;
		if(const_cast<Entity *>(e)->rect.opp().y-rect.org().y<=step_height) {
			rect.org().y+=rec.d.y;
			delta.y+=0.05; //Unstick
			//std::cout<<"HIT SIDEWAYS: "<<rec.d.y<<" UP"<<std::endl;
		}
	}
}

void Entity::update(const Level * l) {
	// adjust for gravity
	if (!fixed) {
		delta.y -= gravity_acceleration;
	}

	// friction
	delta.x*=friction_x;
	delta.y*=friction_y;

	// update position
	delta+=accel;

	if ( delta.x >  max_delta_x) delta.x =  max_delta_x;
	if (-delta.x < -max_delta_x) delta.x = -max_delta_x;
	if ( delta.y >  max_delta_y) delta.y =  max_delta_y;
	if (-delta.y < -max_delta_y) delta.y = -max_delta_y;

	if(delta.y+rect.org().y<0) delta.y=-rect.org().y;

	rect.translate(delta);
	//std::cout<<rect.org().x<<" "<<rect.org().y<<std::endl;

	// don't bother to check collision if we don't move
	// if (delta.x || delta.y) {
		// adjust for collisions
		for (int i = 0; i < l->entities.size(); i++) {
			collides(l->entities[i]);
		}
	// }
}

void Entity::setAnim(int s){
	sprite->setState(s);
}

void Entity::render(glm::mat4 view) {
	sprite->render(view, rect.org().x, rect.org().y);
	rect.render(view);
}

