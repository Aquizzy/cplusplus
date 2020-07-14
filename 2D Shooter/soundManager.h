#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>

using std::cout;

class SoundManager {

public:

	SoundManager();

	void loadMedia();
	void playMusic();
	void playShot();

	~SoundManager();

private:

	Mix_Music* music;
	Mix_Chunk* shot;

};