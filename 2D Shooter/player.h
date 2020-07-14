#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <stdio.h>
#include <string>

#include "ui.h"
#include "bullet.h"
#include "spritesheet.h"
#include "menuManager.h"
#include "gameloop.h"

using std::cout;

class UI;
class Bullet;
class Spitesheet;
class MenuManager;
class Gameloop;

class Player {
public:

	Player(UI*, Spritesheet*, MenuManager*, Gameloop*);

	uint8_t GetHealth() { return health; };
	uint16_t GetxPos() { return xPos; }
	uint16_t GetyPos() { return yPos; }
	   
	void loseHealth(uint8_t);
	void loseLife(uint8_t);
	void draw();
	void update();

	int getScore() { return score; }
	void increaseScore(int _score) { score += _score; ui->setScore(score); }

	void playerMovement(int16_t);

	~Player();

private:

	const uint16_t WIDTH = 576;
	const uint16_t HEIGHT = 910;

	int score = 100;

	bool gameOver;
	int8_t health;
	int8_t lives;
	
	MenuManager* menuManager;
	Gameloop* gameloop;

	uint8_t movementSpeed;
	uint8_t width = 64, height = 64;
	int16_t xPos = 256, yPos = HEIGHT-(2*height);

	SDL_Rect rect;
	Spritesheet* spritesheet;
	UI* ui;
	
};