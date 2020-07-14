#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <stdio.h>
#include <string>

#include "player.h"
#include "spritesheet.h"

using std::cout;

class Player;
class Bullet;
class Spritesheet;

class BulletManager {

public:

	BulletManager(Player*, Spritesheet*);

	void update();
	void draw();
	void shoot();
	bool isShooting();

	Bullet* getBullets(int x) { return bullets[x]; }
	void deleteBullet(int);

	~BulletManager();

private:

	Player* player;
	Bullet* bullets[10];
	Spritesheet* spritesheet;

	bool shooting;

	uint8_t increment;
	uint8_t bulletsOnScreen;

};

class Bullet {	
public:

	Bullet(uint16_t _xPos, Spritesheet* _spritesheet);

	void update();
	void draw();

	SDL_Rect getRect() { return pos; }
	int16_t getYpos() { return yPos; }


	~Bullet();

private:

	Spritesheet* spritesheet;
	SDL_Rect pos;
	
	uint8_t texture;
	uint8_t bulletSpeed;
	int16_t xPos, yPos;

	bool shooting;

};