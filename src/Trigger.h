#ifndef TRIGGER_H
#define TRIGGER_H

class Trigger;

#include <string>
#include <vector>
#include "Level.h"

struct Condition {
	enum Type {
		X_BEFORE,
		X_AFTER,
		Y_BEFORE,
		Y_AFTER,
	};

	Type type;
	float value;

	bool check(Level &);
};

struct Result {
	enum Type {
		DIALOGUE,
		ENABLE,
		DISABLE,
		DELTA
	};

	Type type;

	int arg_in;
	std::string arg_str;
	float arg_x, arg_y;

	void exec(Level &);
};

class Trigger {
public:
	bool enabled;

	Trigger();
	void attempt(Level &);

	std::vector<Condition> conditions;
	std::vector<Result> results;
};

#endif
