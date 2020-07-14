#include "soundManager.h"

///	Loads the media for playing sound effects and music. Begins to play music after its loaded.
SoundManager::SoundManager() {
	loadMedia();
	playMusic();
}

///	Sets pointers to NULL;
SoundManager::~SoundManager() {
	Mix_FreeMusic(music);
	music = NULL;
	Mix_FreeChunk(shot);
	shot = NULL;
}

///	Loads the music from files and assigns them. 
void SoundManager::loadMedia() {
	music = Mix_LoadMUS("sounds/music.wav");
	if (music == NULL) cout << "couldnt load music";
	shot = Mix_LoadWAV("sounds/shot.wav");
	if (shot == NULL) cout << "couldnt load shot" << Mix_GetError();
}

///	Plays the background music.
void SoundManager::playMusic() {
	if (Mix_PlayingMusic() == 0) {
		Mix_PlayMusic(music, -1);
	}
}

///	Plays the laser shot effect.
void SoundManager::playShot() {
	Mix_PlayChannel(-1, shot, 0);
}