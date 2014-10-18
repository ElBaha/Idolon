#ifndef GLHELP_H_INCLUDED
#define GLHELP_H_INCLUDED
#include <stdio.h>
#include <glm/glm.hpp>
#include "GameOptions.h"



void setupGL(){

    glClearColor(0, 0, 0, 1);
    glClearDepth(1.0f);

    glViewport(0, 0, GAME_RESX, GAME_RESY);

    //glMatrixMode(GL_PROJECTION);

    //glLoadIdentity();

    //gluPerspective(57.0, (gameOptions.getInt("XRES",800))/((float)gameOptions.getInt("YRES",600)), 2, 2550);

    //glMatrixMode(GL_MODELVIEW);

    glEnable(GL_DEPTH_TEST);    //http://arcsynthesis.org/gltut/Positioning/Tut05%20Overlap%20and%20Depth%20Buffering.html
    //glDepthMask(GL_TRUE);
    //glDepthFunc(GL_LESS);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_BLEND);


    glEnable ( GL_TEXTURE_2D ) ;

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    setupShaders();
    //setupFrameBuffer();


    glLoadIdentity();


    }

void shutdownGL(){
    cleanupShaders();


}



#endif // GLHELP_H_INCLUDED
