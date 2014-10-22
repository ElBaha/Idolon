#ifndef SOUND_H_INCLUDED
#define SOUND_H_INCLUDED

#include "SDL2/SDL_audio.h"
#include <vector>
#include <string.h>
#include <dirent.h>
//#define NUM_SOUNDS 2


struct sample {
    Uint8 *data;
    //Uint32 dpos;
    Uint32 dlen;
};

struct activeSample {
    //Uint8 *data;
    Uint32 dpos;
    int index;
    float vol;
    //Uint32 dlen;
};

class SoundManager{

public:
SoundManager();
~SoundManager();

void play(string s,float v=1.0);
void silence();
void setVolume(float f);


protected:
void LoadFile(string file);

float vol;
friend void mixaudio(void *unused, Uint8 *stream, int len);

vector<struct sample> soundLib;
list<struct activeSample> curSounds;
map<string,int> soundMap;

};




/*
    #define BUFFSIZE 2048
    Uint8 *sound_buffer;
    Uint8 *sound_buffer2;
    int counter=0;
    int sound_pos = 0;
    int sound_len = BUFFSIZE;
    bool alt=1;
    double Hz[256];
    int size;
    int current=0;
*/



void SoundManager::LoadFile(string file){

    if(string::npos==file.find(".wav"))
    return;

    SDL_AudioSpec wave;
    Uint8 *data;
    Uint32 dlen;
    SDL_AudioCVT cvt;

if ( SDL_LoadWAV(file.c_str(), &wave, &data, &dlen) == NULL ) {
        fprintf(stderr, "Couldn't load %s: %s\n", file.c_str(), SDL_GetError());
        return;
    }
    SDL_BuildAudioCVT(&cvt, wave.format, wave.channels, wave.freq,
                            AUDIO_S16,   2,      22050       );
    cvt.buf = (Uint8*)malloc(dlen*cvt.len_mult);
    memcpy(cvt.buf, data, dlen);
    cvt.len = dlen;
    SDL_ConvertAudio(&cvt);
    SDL_FreeWAV(data);


    struct sample temp;
    soundLib.push_back(temp);
    int end=soundLib.size()-1;

    soundLib.at(end).data=cvt.buf;
    soundLib.at(end).dlen=cvt.len_cvt;
    soundMap[file.substr(7,file.length()-11)]=end;
    cout<<file.substr(/*file.find("/")+1*/7,file.length()-11)<<".wav Loaded"<<endl;
    }

#ifndef __scanDirectory
#define __scanDirectory
void scanDirectory(vector<string> &files, string dirr){

	DIR *dir;
	struct dirent *ent;
	/* open directory stream */
	dir = opendir (dirr.c_str());
	if (dir != NULL) {

		/* print all the files and directories within directory */
		while ((ent = readdir (dir)) != NULL) {
			files.push_back(ent->d_name);
		}

		closedir (dir);
	} else {
		/* could not open directory */
		cerr<<"Could not open "<<dirr<<" Folder!";
	}


}
#endif

/*void initSound(){

    vector<string> files;
	scanDirectory(files,"Sounds");

	for(int x=0;x<files.size();x++){
		LoadFile("Sounds/"+files.at(x));
	}

}*/

/*void denitSound(){

    for(int x=0;x<soundLib.size();x++)
        if ( soundLib.at(x).data ) {
        free(soundLib.at(x).data);
    }

    }*/

void mixaudio(void *unused, Uint8 *stream, int len)
{
    Uint32 amount;
    SoundManager* soundMan=(SoundManager*) unused;


    SDL_memset(stream, 0, len);

    for(list<activeSample>::iterator it= soundMan->curSounds.begin();it!=soundMan->curSounds.end();it++) {
        amount = (soundMan->soundLib.at(it->index).dlen-it->dpos);
        if ( amount > len ) {
            amount = len;
        }
        if(amount==0)
        {
            it=soundMan->curSounds.erase(it);
            continue;
        }

        SDL_MixAudio(stream, &soundMan->soundLib.at(it->index).data[it->dpos], amount, SDL_MIX_MAXVOLUME*it->vol*soundMan->vol);
        it->dpos += amount;
    }

}


SoundManager::SoundManager(){
vol=.5;

    vector<string> files;
	scanDirectory(files,"Sounds");

	for(int x=0;x<files.size();x++){
		LoadFile("Sounds/"+files.at(x));
	}


    SDL_AudioSpec fmt;
    /* Set 16-bit stereo audio at 22Khz */
    fmt.freq = 22050;
    fmt.format = AUDIO_S16;
    fmt.channels = 2;
    fmt.samples = 512;        /* A good value for games */
    fmt.callback = mixaudio;
    fmt.userdata = this;

    /* Open the audio device and start playing sound! */
    if ( SDL_OpenAudio(&fmt, NULL) < 0 ) {
        fprintf(stderr, "Unable to open audio: %s\n", SDL_GetError());
        //exit(1);
    }
    SDL_PauseAudio(0);
}

SoundManager::~SoundManager(){
    for(int x=0;x<soundLib.size();x++)
        if ( soundLib.at(x).data ) {
        free(soundLib.at(x).data);
    }
}

void SoundManager::play(string s,float v){
    int i=soundMap[s];
    if(i>soundLib.size()||i<0){
    cout<<"Sound "<<s<<" was not found\n";
    return;
    }

    struct activeSample temp;

    temp.index=i;
    temp.dpos=0;
    temp.vol=v;

    SDL_LockAudio();

    curSounds.push_back(temp);

    SDL_UnlockAudio();
}

void SoundManager::setVolume(float f){
vol=f;
}


#endif // SOUND_H_INCLUDED
