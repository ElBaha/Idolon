#include "Level.h"
#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include "ShaderHelp.h"
#include "Textures.h"
#include "Input.h"
#include "StatSprite.h"
#include "TweakableMechanics.h"

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
    tempLoc=glGetUniformLocation(getShader("sprite"), "fColor");
    glUniform3f(tempLoc,0,0,0);
    tempLoc=glGetUniformLocation(getShader("sprite"), "fade");
    glUniform1f(tempLoc,0.5);


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

        temp = glm::translate(glm::mat4(),glm::vec3(200.0,100.0,0));
        temp = glm::scale(temp,glm::vec3(200.0,100.0,0));
        tempLoc=glGetUniformLocation(getShader("sprite"), "modelMatrix");
        glUniformMatrix4fv(tempLoc,1, GL_FALSE,&temp[0][0]);

        glBindVertexArray(bg.vao);
        glBindTexture(GL_TEXTURE_2D,getTexture("L1"));
        glDrawArrays(GL_QUADS,0,4);
        glBindVertexArray(0);


        for (int i = 0; i < entities.size(); i++) {
            entities[i]->update(this);
            entities[i]->render(viewMatrix);
        }

        SDL_GL_SwapWindow(window);

        ticks = SDL_GetTicks();
        if (ticks - pticks < ticks_per_frame)
            SDL_Delay(ticks_per_frame - (ticks - pticks));
        pticks = ticks;
    }

}
