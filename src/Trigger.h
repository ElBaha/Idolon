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
		EXISTS,
		NOT_EXISTS,
		DELAY,
	};

	Type type;
	float value;
	unsigned time_delay;
	std::string str;

	bool check(Level &, const Trigger *);
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
	unsigned start_time;
	bool enabled;
public:
	Trigger();
	void enable(bool);
	void attempt(Level &);

	std::vector<Condition> conditions;
	std::vector<Result> results;

	friend class Condition;
};

#endif
