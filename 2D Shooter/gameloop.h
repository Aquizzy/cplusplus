#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>

#include "player.h"
#include "ui.h"
#include "spritesheet.h"
#include "barrier.h"
#include "barrierManager.h"
#include "bullet.h"
#include "enemy.h"
#include "soundManager.h"
#include "menuManager.h"
#include "collision.h"

using std::cout;
class Player;
class BulletManager;
class Collision;

class Gameloop {
public:

	Gameloop(SDL_Renderer*, Spritesheet*, MenuManager*);

	bool init();
	bool getGameOver() { return gameOver; }
	void setGameOver() { gameOver = true; }
	void input();
	void update();
	void draw();

	Player* getPlayer() { return player; }

	~Gameloop();

private:
	bool gameOver = false;

	MenuManager* menuManager;
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event e;

	Collision* collision;
	UI* ui;
	Player* player;
	BarrierManager* barrierManager;
	BulletManager* bulletManager;
	EnemyManager* enemyManager;
	Spritesheet* spritesheet;
	SoundManager* soundManager;
};