#include "Input.h"
#include "Level.h"
#include <SDL2/SDL.h>
#include "GameOptions.h"
#include "TweakableMechanics.h"

int gameInput(bool &quit){
    SDL_Event event;

        while (SDL_PollEvent(&event))
        {

            // check for messages
            switch (event.type)
            {
                // exit if the window is closed
            case SDL_QUIT:
                quit=true;
                break;

                // check for keypresses
            case SDL_KEYDOWN:
                {
                    // exit if ESCAPE is pressed

                    if (event.key.keysym.sym == SDLK_ESCAPE){
                        quit=true;
                        }
                    /*if (event.key.keysym.sym == SDLK_w){
                        mainCam.vel.z=1;
                        }
                    if (event.key.keysym.sym == SDLK_s){
                        mainCam.vel.z=-1;
                        }*/
                    if (event.key.keysym.sym == SDLK_a){
						theLevel->player->accelX = -player_acceleration;

                        }
                    if (event.key.keysym.sym == SDLK_d){
						theLevel->player->accelX = player_acceleration;
                        }



                break;
                }

                case SDL_KEYUP:
                {
                    if (event.key.keysym.sym == SDLK_ESCAPE){
                        quit=true;
                        }
                    if (event.key.keysym.sym == SDLK_a){
						theLevel->player->accelX = 0.;

                        }
                    if (event.key.keysym.sym == SDLK_d){
						theLevel->player->accelX = 0.;
                        }


                    break;
                }


            } // end switch
        } // end of message processing
    return 0;
    }

