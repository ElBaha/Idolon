#include <iostream>
#include <SDL2/SDL.h>
#include "Trigger.h"
using namespace std;

bool Condition::check(Level & l, const Trigger * trig) {
	bool b = true;

	switch (type) {
	case X_BEFORE:
		return l.player->pos.x < value;
	case X_AFTER:
		return l.player->pos.x > value;
	case Y_BEFORE:
		return l.player->pos.y < value;
	case Y_AFTER:
		return l.player->pos.y > value;
	case NOT_EXISTS:
		b = !b;
	case EXISTS:
		for (map<std::string, Entity *>::iterator it = theLevel->entities.begin(); it != theLevel->entities.end(); it++) {
			if (it->first == str) return b;
		}
		return !b;
	case DELAY:
		unsigned cur = SDL_GetTicks();
		return cur - trig->start_time > time_delay;
	}
	return false;
}

void Result::exec(Level & l) {
	switch (type) {
	case DIALOGUE:
		l.memo = arg_str;
		break;
	case ENABLE:
		l.triggers[arg_str]->enable(true);
		break;
	case DISABLE:
		l.triggers[arg_str]->enable(false);
		break;
	case DELTA:
		l.entities[arg_str]->delta.x = arg_x;
		l.entities[arg_str]->delta.y = arg_y;
		break;
	}
}

Trigger::Trigger() {
	enable(true);
}

void Trigger::enable(bool e) {
	start_time = SDL_GetTicks();
	enabled = e;
}

void Trigger::attempt(Level & l) {
	if (!enabled) return;

	// Check conditiions
	for (int i = 0; i < conditions.size(); i++) {
		if (!conditions[i].check(l, this)) return;
	}

	// Trigger executing
	enable(false); // automatically disable self. (you almost always want this)
	for (int i = 0; i < results.size(); i++) {
		results[i].exec(l);
	}
}
