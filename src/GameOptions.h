#ifndef GAMEOPTIONS_H_INCLUDED
#define GAMEOPTIONS_H_INCLUDED

#include <SDL2/SDL.h>
#include <iostream>
#include <map>
#include <fstream>
#include <cstdlib>

using namespace std;

class GameOptions{
    public:

    GameOptions(string s);
    GameOptions();


	int getInt(string s, int def = 0);
	bool getBool(string s, bool def = false);
	float getFloat(string s, float def = 0);
	string getString(string s, string def = "");
	SDL_Keycode getKey(string s, SDL_Keycode def = SDLK_F15);

	void setString(string s, string s2);
	void setInt(string s, int i);

	void writeOptions(string s);

	map <string, string> properties;

	protected:
    void processINILine(string s);
    SDL_Keycode stringToKey(string s);

};

extern GameOptions gameOptions;

#define GAME_RESX gameOptions.getInt("XRES",800)
#define GAME_RESY gameOptions.getInt("YRES",600)


#endif // GAMEOPTIONS_H_INCLUDED
