#include <ctime>
#include <cmath>
#include <cstdlib>
#include <SDL2/SDL.h>


#include "Textures.h"
#include "ShaderHelp.h"
#include "GLHelp.h"
#include "Level.h"
#include "BoneSprite.h"
#include "StatSprite.h"

#define VERSION "Idolon v0.0"

int main ( int argc, char** argv ) {
    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO /*| SDL_INIT_JOYSTICK*/ ) < 0 ) {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    SDL_Window* screen = SDL_CreateWindow(
		VERSION,
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		gameOptions.getInt("XRES",800), gameOptions.getInt("YRES",600),
		(gameOptions.getBool("FULLSCREEN") ? SDL_WINDOW_FULLSCREEN_DESKTOP:0) | SDL_WINDOW_OPENGL
	);

    SDL_GLContext glcontext=SDL_GL_CreateContext(screen);
    SDL_ShowCursor(true);
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }

    if ( !screen ) {
        printf("Unable to start video: %s\n", SDL_GetError());
        cout<<gameOptions.getInt("XRES",800)<<"x"<<gameOptions.getInt("YRES",600)<<endl;
        return 1;
    }

    SDL_DisplayMode current;
    int should_be_zero = SDL_GetCurrentDisplayMode(0, &current);
    if(should_be_zero != 0)
        printf("Could not get display mode for video display #%d: %s", 0, SDL_GetError());
    else
        printf("Display #%d: current display mode is %dx%dpx @ %dhz. \n", 0, current.w, current.h, current.refresh_rate);

    if(gameOptions.getBool("FULLSCREEN")) {
        gameOptions.setInt("XRES",current.w);
        gameOptions.setInt("YRES",current.h);
    }


    //inialize things
    loadTextures();
    setupGL();
    srand(time(NULL));



    Level l;
    theLevel = &l;

	// TODO don't hardcode the player
	l.player = new Entity();
	l.player->fixed = false;
	l.entities[0] = l.player;
	l.load("Levels/1"); // TODO ideally don't use a relative path
    l.run(screen);

    //cleanup
    shutdownGL();
    unloadTextures();
    SDL_GL_DeleteContext(glcontext);



    // all is well ;)
    printf("Exited cleanly\n");
    return 0;
}
