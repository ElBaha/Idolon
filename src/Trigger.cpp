#include <iostream>
#include "Trigger.h"
using namespace std;

bool Condition::check(Level & l) {
	switch (type) {
	case X_BEFORE:
		return l.player->pos.x < value;
	case X_AFTER:
		return l.player->pos.x > value;
	case Y_BEFORE:
		return l.player->pos.y < value;
	case Y_AFTER:
		return l.player->pos.y > value;
	}
	return false;
}

void Result::exec(Level & l) {
	switch (type) {
	case DIALOGUE:
		//TODO actual dialogue
		cout << arg_str << endl;
		break;
	case ENABLE:
		l.triggers[arg_in]->enabled = true;
		break;
	case DISABLE:
		l.triggers[arg_in]->enabled = false;
		break;
	}
}

Trigger::Trigger() {
	enabled = true;
}

void Trigger::attempt(Level & l) {
	if (!enabled) return;

	// Check conditiions
	for (int i = 0; i < conditions.size(); i++) {
		if (!conditions[i].check(l)) return;
	}

	// Trigger executing
	for (int i = 0; i < results.size(); i++) {
		results[i].exec(l);
	}
}
