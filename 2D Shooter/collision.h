#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>

#include "bullet.h"
#include "enemy.h"
#include "barrierManager.h"
#include "barrier.h"
#include "player.h"

class BulletManager;
class Bullet;
class EnemyManager;
class Enemy;
class Player;

class Collision {

public:

	Collision(BulletManager*, EnemyManager*, BarrierManager*, Player*);
	
	void checkCollision();
	bool collisionCheckEnemy(SDL_Rect, SDL_Rect);
	bool collisionCheckSpaceship(SDL_Rect, SDL_Rect);
	bool collisionCheckBarrier(SDL_Rect, SDL_Rect);
	
	void update();
	
	
	~Collision();

private:

	BulletManager* bulletManager;
	BarrierManager* barrierManager;
	EnemyManager* enemyManager;
	Player* player;

	Spaceship* spaceship;
	Enemy* enemy[7][5];
	Bullet* bullet[10];
	Barrier* barrier[8];
};