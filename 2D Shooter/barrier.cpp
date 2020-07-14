#include "barrier.h"

///	This obtains references and sets the barriers; health, left/right and destroyed.
///	@param _pos	This is the position, width and height for the barrier to be spawned.
///	@param _spritesheet This is a reference to the spritesheet which will draw to the screen.
Barrier::Barrier(SDL_Rect _pos, Spritesheet* _spritesheet) {
	pos = _pos;
	spritesheet = _spritesheet;
	health = 100;
	destroyed = false;

	if (pos.x % 64){
		left = false;
		texture = spritesheet->rightBarrier100;
	}
	else {
		left = true;
		texture = spritesheet->leftBarrier100;
	}
}

///	Sets all pointers to NULL.
Barrier::~Barrier() {
	barrierManager = NULL;
	spritesheet = NULL;
}

///	Changes the texture to render depending on the health of the barrier.
/// @param _damageAmount is the amount of lifes the player loses.
void Barrier::loseHealth(uint8_t _damageAmount) {
	health -= _damageAmount;
	if ((75 < health) && (health <= 100)) {
		if (left) texture = spritesheet->leftBarrier100;
		else texture = spritesheet->rightBarrier100;
	}
	else if ((50 < health) && (health <= 75)) {
		if (left) texture = spritesheet->leftBarrier75;
		else texture = spritesheet->rightBarrier75;
	}
	else if ((25 < health) && (health <= 50)) {
		if (left) texture = spritesheet->leftBarrier50;
		else texture = spritesheet->rightBarrier50;
	}
	else if ((0 < health) && (health <= 25)) {
		if (left) texture = spritesheet->leftBarrier25;
		else texture = spritesheet->rightBarrier25;
	}
	else if(health < 0){
		destroyed = true;
	}
}

///	Renders the barrier to the screen, if it has not yet been destroyed.
void Barrier::draw() {
	spritesheet->draw(texture, &pos);
}