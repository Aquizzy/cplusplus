#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <stdio.h>
#include <string>

#include "spritesheet.h"

using std::cout;
using std::to_string;

class Spritesheet;

class UI {
public:

	UI(SDL_Renderer*, Spritesheet*);

	void health(uint8_t);
	void lives(uint8_t);
	void draw();
	void drawFont(const char*, int, int, int);

	void setScore(int _score) { score = _score; }
	void setWaves(int _waves) { wave = _waves; }

	~UI();

private:

	int8_t playerHealth, playerLives;
	uint8_t healthWidth, healthHeight;
	uint16_t xPosHealth, yPosHealth;
	uint16_t score;
	uint8_t wave;

	std::string scoreText;
	std::string waveText;

	SDL_Renderer* renderer;
	Spritesheet* spritesheet;
	SDL_Rect healthPos;
	SDL_Rect livesSprite[3];
};