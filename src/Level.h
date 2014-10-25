#ifndef LEVEL_H
#define LEVEL_H

class Level;

#include <map>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include "Entity.h"
#include "stdvao.h"

class Level {
public:
    Level();
    ~Level();
    void run(SDL_Window* window);
	void load(const char *);
    void setup();

    float camX,camY;
    vao::CenterSquare bg;
    vao::CenterSquare fg;

	Entity * player;
	std::map<int, Entity *> entities;

};

extern Level* theLevel;

#endif // LEVEL_H
