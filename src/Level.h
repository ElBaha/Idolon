#ifndef LEVEL_H
#define LEVEL_H

class Level;

#include <map>
#include <string>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include "Entity.h"
#include "Trigger.h"
#include "stdvao.h"

using namespace std;

class Level {
public:
    Level();
    ~Level();
    void run(SDL_Window* window);
	void load(const char *);
    void setup();
	void use();
	void renderStat();

    float camX,camY;
	std::string bg_name;
	float bg_width, bg_height;
    vao::CenterSquare bg;
    vao::CenterSquare fg;

	Entity * player;
	std::map<std::string, Entity *> entities;
	std::map<std::string, Trigger *> triggers;
	string memo;
};

extern Level* theLevel;

#endif // LEVEL_H
