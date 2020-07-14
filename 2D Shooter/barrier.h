#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <stdio.h>

#include "barrierManager.h"
#include "spritesheet.h"

using std::cout;

class BarrierManager;
class Spritesheet;

class Barrier {

public:

	Barrier(SDL_Rect, Spritesheet*);

	void loseHealth(uint8_t);
	void draw();

	SDL_Rect getRect() { return pos; }

	bool isDead() { return destroyed; }

	~Barrier();

private:

	BarrierManager* barrierManager;
	SDL_Rect pos;
	Spritesheet* spritesheet;

	bool left;
	bool destroyed;
	int8_t texture;
	int8_t health;	

};