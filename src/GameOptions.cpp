#include "GameOptions.h"
#include <sstream>
GameOptions gameOptions("settings.ini");

SDL_Keycode GameOptions::stringToKey(string s){

	if(s=="a") return SDLK_a;
	if(s=="b") return SDLK_b;
	if(s=="c") return SDLK_c;
	if(s=="d") return SDLK_d;
	if(s=="e") return SDLK_e;
	if(s=="f") return SDLK_f;
	if(s=="g") return SDLK_g;
	if(s=="h") return SDLK_h;
	if(s=="i") return SDLK_i;
	if(s=="j") return SDLK_j;
	if(s=="k") return SDLK_k;
	if(s=="l") return SDLK_l;
	if(s=="m") return SDLK_m;
	if(s=="n") return SDLK_n;
	if(s=="o") return SDLK_o;
	if(s=="p") return SDLK_p;
	if(s=="q") return SDLK_q;
	if(s=="r") return SDLK_r;
	if(s=="s") return SDLK_s;
	if(s=="t") return SDLK_t;
	if(s=="u") return SDLK_u;
	if(s=="v") return SDLK_v;
	if(s=="w") return SDLK_w;
	if(s=="x") return SDLK_x;
	if(s=="y") return SDLK_y;
	if(s=="z") return SDLK_z;
	if(s=="1") return SDLK_1;
	if(s=="2") return SDLK_2;
	if(s=="3") return SDLK_3;
	if(s=="4") return SDLK_4;
	if(s=="5") return SDLK_5;
	if(s=="6") return SDLK_6;
	if(s=="7") return SDLK_7;
	if(s=="8") return SDLK_8;
	if(s=="9") return SDLK_9;
	if(s=="0") return SDLK_0;

	if(s=="k1") return SDLK_KP_1;
	if(s=="k2") return SDLK_KP_2;
	if(s=="k3") return SDLK_KP_3;
	if(s=="k4") return SDLK_KP_4;
	if(s=="k5") return SDLK_KP_5;
	if(s=="k6") return SDLK_KP_6;
	if(s=="k7") return SDLK_KP_7;
	if(s=="k8") return SDLK_KP_8;
	if(s=="k9") return SDLK_KP_9;
	if(s=="k0") return SDLK_KP_0;
	if(s=="k+") return SDLK_KP_PLUS;
	if(s=="k-") return SDLK_KP_MINUS;
	if(s=="k*") return SDLK_KP_MULTIPLY;
	if(s=="k/") return SDLK_KP_DIVIDE;
	if(s=="kenter") return SDLK_KP_ENTER;
	if(s=="k.") return SDLK_KP_PERIOD;

	if(s=="insert") return SDLK_INSERT;
	if(s=="home") return SDLK_HOME;
	if(s=="pgup") return SDLK_PAGEUP;
	if(s=="pgdown") return SDLK_PAGEDOWN;
	if(s=="end") return SDLK_END;
	if(s=="delete") return SDLK_DELETE;

	if(s=="ralt") return SDLK_RALT;
	if(s=="rshift") return SDLK_RSHIFT;
	if(s=="rctrl") return SDLK_RCTRL;
	if(s=="lalt") return SDLK_LALT;
	if(s=="lshift") return SDLK_LSHIFT;
	if(s=="lctrl") return SDLK_LCTRL;
	if(s=="up") return SDLK_UP;
	if(s=="down") return SDLK_DOWN;
	if(s=="right") return SDLK_RIGHT;
	if(s=="left") return SDLK_LEFT;

	if(s=="`") return SDLK_BACKQUOTE;
	if(s=="[") return SDLK_LEFTBRACKET;
	if(s=="]") return SDLK_RIGHTBRACKET;
	if(s=="-") return SDLK_MINUS;
	if(s=="=") return SDLK_EQUALS;
	if(s=="backspace") return SDLK_BACKSPACE;
	if(s=="/") return SDLK_SLASH;
	if(s=="\\") return SDLK_BACKSLASH;
	if(s==",") return SDLK_COMMA;
	if(s==".") return SDLK_PERIOD;
	if(s==";") return SDLK_SEMICOLON;
	if(s=="'") return SDLK_QUOTE;

	if(s=="f1") return SDLK_F1;
	if(s=="f2") return SDLK_F2;
	if(s=="f3") return SDLK_F3;
	if(s=="f4") return SDLK_F4;
	if(s=="f5") return SDLK_F5;
	if(s=="f6") return SDLK_F6;
	if(s=="f7") return SDLK_F7;
	if(s=="f8") return SDLK_F8;
	if(s=="f9") return SDLK_F9;
	if(s=="f10") return SDLK_F10;
	if(s=="f11") return SDLK_F11;
	if(s=="f12") return SDLK_F12;
	if(s=="f13") return SDLK_F13;
	if(s=="f14") return SDLK_F14;
	if(s=="f15") return SDLK_F15;

	if(s=="esc") return SDLK_ESCAPE;
	//if(s=="pb") return SDLK_BREAK;

	return SDLK_F15;
}

void GameOptions::processINILine(string s){

	int eq=s.find('=',0);
	string mod=s.substr(0,eq);
	string mew=s.substr(eq+1);


	/*if(mod=="XRES")
		RESOLUTION_X=atoi(mew.c_str());
	else if(mod=="YRES")
		RESOLUTION_Y=atoi(mew.c_str());
	else if(mod=="FULLSCREEN")
		fullScreen=mew=="true";
    else*/
        properties[mod]=mew;

}

GameOptions::GameOptions(string s){

	ifstream inFile(s.c_str());
	std::string temp;
	while(inFile){

		getline(inFile,temp);
		if(temp[0]!='#')
			processINILine(temp);
	}

}

GameOptions::GameOptions(){}

int GameOptions::getInt(string s, int def){
    if(properties.count(s))
    return atoi(properties[s].c_str());
    return def;
    }

bool GameOptions::getBool(string s, bool def){
	if(properties.count(s))
    return properties[s]=="true";
    return def;
	}

float GameOptions::getFloat(string s, float def){
    if(properties.count(s))
    return atof(properties[s].c_str());
    return def;
	}

string GameOptions::getString(string s, string def){
	if(properties.count(s))
    return properties[s];
    return def;
	}

SDL_Keycode GameOptions::getKey(string s, SDL_Keycode def){
	if(properties.count(s))
    return stringToKey(properties[s]);
    return def;
	}

void GameOptions::setString(string s, string s2){
    properties[s]=s2;
}

void GameOptions::setInt(string s, int i){
    stringstream ss;
    ss<<i;
    properties[s]=ss.str();
}

void GameOptions::writeOptions(string s){

    ofstream out(s.c_str());
	std::string temp;
	for(map<string,string>::iterator it=properties.begin();it!=properties.end();it++){

	if(!it->second.empty())
	out<<it->first<<"="<<it->second<<endl;
	}

    out.close();

}
