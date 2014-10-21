#include "Level.h"
#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include "ShaderHelp.h"
#include "Textures.h"
#include "Input.h"
#include "StatSprite.h"

Level* theLevel = NULL;

Level::Level()
{
    camX=camY=10;
	player = NULL;

}

Level::~Level()
{
    //dtor
}

void Level::setup(){
    glClearColor(.5, .5, 1, 1);

	glm::mat4 temp;
	temp=glm::ortho(0.0,100.0,0.0,100.0,-50.0,50.0);
	/*int tempLoc=glGetUniformLocation(getShader("debris"), "projectionMatrix");
	glUniformMatrix4fv(tempLoc,1, GL_FALSE,&temp[0][0]);

	glUseProgram(getShader("laser"));
	tempLoc=glGetUniformLocation(getShader("laser"), "projectionMatrix");
	glUniformMatrix4fv(tempLoc,1, GL_FALSE,&temp[0][0]);

	glUseProgram(getShader("mod"));
	tempLoc=glGetUniformLocation(getShader("mod"), "projectionMatrix");
	glUniformMatrix4fv(tempLoc,1, GL_FALSE,&temp[0][0]);*/

	glUseProgram(getShader("sprite"));
	GLuint tempLoc=glGetUniformLocation(getShader("sprite"), "projectionMatrix");
	glUniformMatrix4fv(tempLoc,1, GL_FALSE,&temp[0][0]);
	tempLoc=glGetUniformLocation(getShader("sprite"), "sampler");
    glUniform1i(tempLoc,0);


}

void Level::run(SDL_Window* window) {

    setup();
    bool quit=false;

    while(!quit) {
        gameInput(quit);


        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glm::mat4 viewMatrix = glm::translate(glm::mat4(),glm::vec3(camX,camY,0));

		for (int i = 0; i < entities.size(); i++) {
			entities[i]->render(viewMatrix);
		}


        glm::mat4 temp;
        glUseProgram(getShader("sprite"));
        GLuint tempLoc=glGetUniformLocation(getShader("sprite"), "viewMatrix");
        glUniformMatrix4fv(tempLoc,1, GL_FALSE,&temp[0][0]);

        temp = glm::translate(glm::mat4(),glm::vec3(50.0,50.0,0));
        temp = glm::scale(temp,glm::vec3(50.0,50.0,0));
        tempLoc=glGetUniformLocation(getShader("sprite"), "modelMatrix");
        glUniformMatrix4fv(tempLoc,1, GL_FALSE,&temp[0][0]);

        glBindVertexArray(bg.vao);
        glBindTexture(GL_TEXTURE_2D,getTexture("back"));
        glDrawArrays(GL_QUADS,0,4);
        glBindVertexArray(0);


//printf("%s\n",gluErrorString(glGetError()));

        SDL_GL_SwapWindow(window);
    }

}
