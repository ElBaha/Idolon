#ifndef GLHELP_H_INCLUDED
#define GLHELP_H_INCLUDED

#include <stdio.h>
#include <glm/glm.hpp>
#include "GameOptions.h"

void setupGL(){

    glClearColor(0, 0, 0, 1);
    glClearDepth(1.0f);

    glViewport(0, 0, GAME_RESX, GAME_RESY);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_BLEND);


    glEnable ( GL_TEXTURE_2D ) ;
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    setupShaders();
    glLoadIdentity();
}

void shutdownGL(){
    cleanupShaders();
}

#endif // GLHELP_H_INCLUDED
