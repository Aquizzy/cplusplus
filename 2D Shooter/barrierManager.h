#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <stdio.h>
#include <string>

#include "barrier.h"
#include "spritesheet.h"
using std::cout;

class Barrier;
class Spritesheet;

class BarrierManager {

public:

	BarrierManager(Spritesheet*);

	void draw();
	void damage(uint8_t, uint8_t);

	Barrier* getBarrier(int i) { return barrier[i]; }
	void deleteBarrier(int,int);

	~BarrierManager();

private:

	Barrier* barrier[8];
	Spritesheet* spritesheet;
	SDL_Rect barrierPos[8];

};