#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <stdio.h>
#include <string>

#include "spritesheet.h"
#include "ui.h"

using std::cout;
using std::endl;

class Enemy;
class Spaceship;
class Spritesheet;
class UI;

class EnemyManager {

public:

	EnemyManager(Spritesheet*, UI*);

	void draw();
	void update();
	void spawnWave();
	void spawnSpaceshipRight();
	void spawnSpaceshipLeft();

	Enemy* getEnemies(int x, int y) { return enemy[x][y]; }
	Spaceship* getSpaceship() { return spaceship; }

	void deleteEnemy(int x, int y) { delete enemy[x][y]; enemy[x][y] = NULL; dead++; }
	void deleteSpaceship() { delete spaceship; spaceship = NULL; }

	~EnemyManager();

private:

	UI* ui;

	uint8_t wave;
	uint8_t count;
	uint8_t dead;
	Spritesheet* spritesheet;

	SDL_Rect row[7][5];
	Enemy* enemy[7][5];

	bool left, right;
	int enemyPositions = 64;

	Spaceship* spaceship;
	SDL_Rect spaceshipRectRight;
	SDL_Rect spaceshipRectLeft;

};

class Enemy {

public:

	Enemy(uint8_t _j, SDL_Rect _rect, Spritesheet* _spritesheet);

	void setSprite(uint8_t _j);
	void draw();
	void update();
	void moveLeft();
	void moveRight();
	void moveDown();

	SDL_Rect getRect() { return rect; }

	~Enemy();

private:

	uint8_t width, height;
	uint8_t movementSpeed;
	int8_t xPos, yPos;

	SDL_Renderer* renderer;
	SDL_Rect rect;

	uint8_t sprite[2];

	Spritesheet* spritesheet;

};

class Spaceship {
public:

	Spaceship(SDL_Rect _rect, bool _left, Spritesheet* _spritesheet);

	void draw();
	void update();
	void movement();

	SDL_Rect getRect() { return rect; }

	~Spaceship();

private:

	Spritesheet* spritesheet;
	SDL_Rect rect;

	uint8_t sprite;
	uint8_t movementSpeed;
	uint8_t height, width;
	int16_t xPos, yPos;


	bool left;
	bool alive;

};