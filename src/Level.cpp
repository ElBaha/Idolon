#include "Level.h"
#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include "ShaderHelp.h"
#include "Textures.h"
#include "Input.h"
#include "StatSprite.h"
#include "TweakableMechanics.h"
#include "GameOptions.h"

#include <iostream>
using namespace std;

Level* theLevel = NULL;

Level::Level() {
    camX=camY=0;
    player = NULL;

}

Level::~Level() {
    //if(player)
    //delete player;

    for(int x=0; x<entities.size(); x++)
        delete entities[x];
}

void Level::setup() {
    glClearColor(.5, .5, 1, 1);

    glm::mat4 temp;
    temp=glm::ortho(0.0,100.0*GAME_RESX/GAME_RESY,0.0,100.0,-50.0,50.0);

    glUseProgram(getShader("sprite"));
    GLuint tempLoc=glGetUniformLocation(getShader("sprite"), "projectionMatrix");
    glUniformMatrix4fv(tempLoc,1, GL_FALSE,&temp[0][0]);
    tempLoc=glGetUniformLocation(getShader("sprite"), "sampler");
    glUniform1i(tempLoc,0);
    tempLoc=glGetUniformLocation(getShader("sprite"), "fColor");
    glUniform3f(tempLoc,0,0,0);
    tempLoc=glGetUniformLocation(getShader("sprite"), "fade");
    glUniform1f(tempLoc,0.5);

    temp=glm::ortho(0.0,100.0,0.0,100.0,-50.0,50.0);
    glUseProgram(getShader("ui"));
    tempLoc=glGetUniformLocation(getShader("ui"), "projMatrix");
    glUniformMatrix4fv(tempLoc,1, GL_FALSE,&temp[0][0]);
    tempLoc=glGetUniformLocation(getShader("ui"), "sampler");
    glUniform1i(tempLoc,0);
    tempLoc=glGetUniformLocation(getShader("ui"), "textColor");
    glUniform3f(tempLoc,1,0,0);
    tempLoc=glGetUniformLocation(getShader("ui"), "mode");
    glUniform1i(tempLoc,2);
}

void Level::renderStat(){

	glm::mat4 temp=glm::translate(glm::mat4(),glm::vec3(40,96,5));
	glUseProgram(getShader("ui"));
        GLuint tempLoc=glGetUniformLocation(getShader("ui"), "modelMatrix");
        glUniformMatrix4fv(tempLoc,1, GL_FALSE,&temp[0][0]);

	TextRenderer rend("TextAB");
	rend.setRenderSize(2,3);

	rend.renderString("Hello");

}

void Level::load(const char * filename) {
	const int buf_size = 512;
	char buf[buf_size];

	FILE * f = fopen(filename, "rb");
	if (f == NULL) {
		fprintf(stderr, "Could not open level file '%s'.\n", filename);
		exit(EXIT_FAILURE);
	}

	// TODO fix so entities don't overwrite each other (potential lost memory during lod)
	while (!feof(f)) {
		int c = fgetc(f);
		switch (c) {
		case '#':
			while (fgetc(f) != '\n' && !feof(f));
			break;
		case 'B':
			assert(3 == fscanf(f, " %512s %g %g\n", buf, &bg_width, &bg_height));
			bg_name = string(buf);
			break;
		case 's':
			int id;
			float x, y, w, h;
			assert(6 == fscanf(f, " %d %512s %g %g %g %g\n", &id, buf, &x, &y, &w, &h));
			entities[id] = new Entity(string(buf), x, y, w, h);
			break;
		}
	}

	fclose(f);
}

void Level::run(SDL_Window* window) {

    setup();
    bool quit=false;
    float fade=0;

    int ticks, pticks = SDL_GetTicks();

    while(!quit) {
        SDL_Delay(20);
        gameInput(quit);

        camX=-player->pos.x+50;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glm::mat4 viewMatrix = glm::translate(glm::mat4(),glm::vec3(camX,camY,0));

        glm::mat4 temp;
        glUseProgram(getShader("sprite"));
        GLuint tempLoc=glGetUniformLocation(getShader("sprite"), "viewMatrix");
        glUniformMatrix4fv(tempLoc,1, GL_FALSE,&viewMatrix[0][0]);
        tempLoc=glGetUniformLocation(getShader("sprite"), "fade");
        glUniform1f(tempLoc,fade);
        if(fade<1)
            fade+=.002;

        temp = glm::translate(glm::mat4(),glm::vec3(bg_width,bg_height,0));
        temp = glm::scale(temp,glm::vec3(bg_width,bg_height,0));
        tempLoc=glGetUniformLocation(getShader("sprite"), "modelMatrix");
        glUniformMatrix4fv(tempLoc,1, GL_FALSE,&temp[0][0]);

        glBindVertexArray(bg.vao);
        glBindTexture(GL_TEXTURE_2D,getTexture(bg_name));
        glDrawArrays(GL_QUADS,0,4);
        glBindVertexArray(0);


        for (map<int, Entity *>::iterator it = entities.begin(); it != entities.end(); ++it) {
            it->second->update(this);
            it->second->render(viewMatrix);
        }

	renderStat();

        SDL_GL_SwapWindow(window);

        ticks = SDL_GetTicks();
        if (ticks - pticks < ticks_per_frame)
            SDL_Delay(ticks_per_frame - (ticks - pticks));
        pticks = ticks;
    }

}

void Level::use(){

	for (int i = 0; i < entities.size(); i++) {
		if(entities[i]->canUse(player))
            		entities[i]->use(NULL);
        }

}
