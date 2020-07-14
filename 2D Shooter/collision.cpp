#include "collision.h"


Collision::Collision(BulletManager* _bulletManager, EnemyManager* _enemyManager, BarrierManager* _barrierManager, Player* _player) {
	bulletManager = _bulletManager;
	enemyManager = _enemyManager;
	barrierManager = _barrierManager;
	player = _player;
}

Collision::~Collision() {
	bulletManager = nullptr;
	enemyManager = nullptr;
}

void Collision::checkCollision() {
	///	if y isnt within the bottom enemy do nothing.
	///if it is check agaisnt all enemies.

	//if y is passed enemies check against spaceship.

	//SDL_Rect lowestEnemy = enemy[6][4]->getRect();
	//SDL_Rect highestEnemy = enemy[6][0]->getRect();
	//int y = lowestEnemy.y + 64;
	//cout << y << endl;

	///	Cheking for enemy collision.
	for (int i = 0; i < 10; i++)
	{
		bullet[i] = bulletManager->getBullets(i);
		if (bullet[i] != NULL) {
			if (bullet[i]->getRect().y < 578) {
				for (int x = 0; x < 7; x++)
				{
					for (int y = 0; y < 5; y++)
					{
						if (enemy[x][y] != NULL) {
							if (collisionCheckEnemy(bullet[i]->getRect(), enemy[x][y]->getRect())) {
								bulletManager->deleteBullet(i);
								enemyManager->deleteEnemy(x, y);
								player->increaseScore(100);
								enemy[x][y] = NULL;
							}
						}
					}
				}
			}
		}
		bullet[i] = NULL;
	}

	///	Checking for spaceship collision.
	for (int i = 0; i < 10; i++)
	{
		bullet[i] = bulletManager->getBullets(i);
		if (bullet[i] != NULL) {
			if (bullet[i]->getRect().y < 300) {
				if (spaceship != NULL) {
					if (collisionCheckSpaceship(bullet[i]->getRect(), spaceship->getRect())) {
						bulletManager->deleteBullet(i);
						enemyManager->deleteSpaceship();
						player->increaseScore(250);
						spaceship = NULL;
						bullet[i] = NULL;
					}
				}
			}
		}
	}

	///	Checking for barrier collision.
	for (int i = 0; i < 10; i++)
	{
		bullet[i] = bulletManager->getBullets(i);
		if (bullet[i] != NULL) {
			if (bullet[i]->getRect().y < 1000) {
				for (int x = 0; x < 8; x++)
				{
					if (barrier[x] != NULL) {
						if (collisionCheckBarrier(bullet[i]->getRect(), barrier[x]->getRect())) {
							if (x >= 4) {
								barrierManager->damage(x-4,5);							
								if (barrier[x]->isDead()) {
									barrierManager->deleteBarrier(x, x - 4);
									barrier[x] = NULL;
									barrier[x - 4] = NULL;
								}
							}
							else
							{
								barrierManager->damage(x,5);
								if (barrier[x]->isDead()) {
									barrierManager->deleteBarrier(x, x + 4);
									barrier[x] = NULL;
									barrier[x + 4] = NULL;
								}
							}
							bulletManager->deleteBullet(i);
						}
					}
				}
				bullet[i] = NULL;
			}
		}
	}
}

///	@warning this makes spaceship hitbox broken.
bool Collision::collisionCheckEnemy(SDL_Rect _a, SDL_Rect _b) {
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = _a.x + 28;
	rightA = _a.x + _a.w - 28;
	topA = _a.y + 20;
	bottomA = _a.y + _a.h - 20;

	//Calculate the sides of rect B
	leftB = _b.x + 10;
	rightB = _b.x + _b.w - 10;
	topB = _b.y + 3;
	bottomB = _b.y + _b.h - 3;

	//If any of the sides from A are outside of B
	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	//If none of the sides from A are outside B
	return true;
}
bool Collision::collisionCheckSpaceship(SDL_Rect _a, SDL_Rect _b) {
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = _a.x + 28;
	rightA = _a.x + _a.w - 28;
	topA = _a.y + 20;
	bottomA = _a.y + _a.h - 20;

	//Calculate the sides of rect B
	leftB = _b.x + 10;
	rightB = _b.x + _b.w - 10;
	topB = _b.y + 3;
	bottomB = _b.y + _b.h - 3;

	//If any of the sides from A are outside of B
	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	//If none of the sides from A are outside B
	return true;
}
bool Collision::collisionCheckBarrier(SDL_Rect _a, SDL_Rect _b) {
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = _a.x + 28;
	rightA = _a.x + _a.w - 28;
	topA = _a.y + 20;
	bottomA = _a.y + _a.h - 20;

	//Calculate the sides of rect B
	leftB = _b.x;
	rightB = _b.x + _b.w;
	topB = _b.y + 8;
	bottomB = _b.y + _b.h;

	//If any of the sides from A are outside of B
	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	//If none of the sides from A are outside B
	return true;
}

void Collision::update() {

	//	Enemy.
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (enemyManager->getEnemies(i, j) != NULL) {
				enemy[i][j] = enemyManager->getEnemies(i, j);
			}
		}
	}

	//	Spaceship.
	spaceship = enemyManager->getSpaceship();

	//	Bullets.
	for (int x = 0; x < 10; x++)
	{
		if (bulletManager->getBullets(x) != NULL) {
			bullet[x] = bulletManager->getBullets(x);
		}
	}

	for (int i = 0; i < 8; i++)
	{
		barrier[i] = barrierManager->getBarrier(i);
	}
	checkCollision();
}