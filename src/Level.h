#ifndef LEVEL_H
#define LEVEL_H

class Level;

#include <vector>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include "Entity.h"
#include "stdvao.h"

class Level {
public:
    Level();
    ~Level();
    void run(SDL_Window* window);
    void setup();
	void use();

    float camX,camY;
    vao::CenterSquare bg;
    vao::CenterSquare fg;

	Entity * player;
	std::vector<Entity *> entities;

};

extern Level* theLevel;

#endif // LEVEL_H
