#include "enemy.h"

///	Sets the side to move and spawn the enemies.
/// @param _spritesheet	This is a reference to the spritesheet which will draw to the screen.
EnemyManager::EnemyManager(Spritesheet* _spritesheet, UI* _ui) {
	spritesheet = _spritesheet;
	ui = _ui;
	count = 0;
	left = true;
	right = false;
	wave = 1;

	spawnWave();
	spawnSpaceshipLeft();
}

///	Sets all pointers to NULL.
EnemyManager::~EnemyManager() {
	spritesheet = NULL;
	delete enemy[7][5];
	enemy[7][5] = NULL;
	delete spaceship;
	spaceship = NULL;
}

///	Calls all enemies to draw on screen.
void EnemyManager::draw() {
	for (uint8_t i = 0; i < 7; i++)
	{
		for (uint8_t j = 0; j < 5; j++)
		{
			if (enemy[i][j] != NULL) enemy[i][j]->draw();
		}
	}
	if (spaceship != NULL)spaceship->draw();
}


///	Updates all enemies to move. The basic enemies to move side to side. 
///	The spaceship to move continously until the border is hit.
void EnemyManager::update() {
	if (left) enemyPositions -= 1;
	if (right) enemyPositions += 1;
	if (enemyPositions <= 0) {
		right = true;
		left = false;
		count++;
	}
	if (enemyPositions >= 128) {
		right = false;
		left = true;
		count++;
	}
	if (count != 3) {
		for (uint8_t i = 0; i < 7; i++)
		{
			for (uint8_t j = 0; j < 5; j++)
			{
				if (enemy[i][j] != NULL) {
					if (left) {
						enemy[i][j]->moveLeft();
					}
					else if (right) {
						enemy[i][j]->moveRight();
					}
				}
			}
		}
	}
	else {
		for (uint8_t i = 0; i < 7; i++)
		{
			for (uint8_t j = 0; j < 5; j++)
			{
				if (enemy[i][j] != NULL) {
					enemy[i][j]->moveDown();
				}
			}
		}
		count = 0;
	}
	if (dead == 35) {
		dead = 0;
		SDL_Delay(2000);
		spawnWave();
		wave++;
		ui->setWaves(wave);
		cout << (int)wave << std::endl;

	}
	if(spaceship != NULL) spaceship->movement();
}

///	Spawns a chunk of normal waves.
void EnemyManager::spawnWave() {
	enemyPositions = 64;
	for (uint8_t i = 0; i < 7; i++)
	{
		for (uint8_t j = 0; j < 5; j++)
		{
			row[i][j] = { 64 + (i * 64), 128 + (j * 64), 64, 64 };
			enemy[i][j] = new Enemy(j, row[i][j], spritesheet);
		}
	}
}

///	Spawns a spaceship that moves to the right.
void EnemyManager::spawnSpaceshipRight() {
	spaceshipRectRight = { 0, 32, 64, 64 };
	spaceship = new Spaceship(spaceshipRectRight, false, spritesheet);
}

///	Spawns a spaceship that moves to the left.
void EnemyManager::spawnSpaceshipLeft() {
	spaceshipRectLeft = { 464, 32, 64, 64 };
	spaceship = new Spaceship(spaceshipRectLeft, true, spritesheet);
}

///	Sets the enemies sprite, postion, width, height and movement speed.
///	@param _j Is the ID of which enemy sprite to be used.
///	@param _rect Holds the sprite postion and dimensions.
/// @param _spritesheet This is a reference to the spritesheet which will draw to the screen.
Enemy::Enemy(uint8_t _j, SDL_Rect _rect, Spritesheet* _spritesheet) {
	setSprite(_j);
	rect = _rect;
	rect.w = width = 64;
	rect.h = height = 64;
	spritesheet = _spritesheet;
	movementSpeed = 1;
}

Enemy::~Enemy() {
	renderer = NULL;
	spritesheet = NULL;
}

///	Draws the enemy on the screen.
void Enemy::draw() {
	if (SDL_GetTicks() % 1000 <= 500)
	{
		spritesheet->draw(sprite[0], &rect);
	}
	else {
		spritesheet->draw(sprite[1], &rect);
	}

}

///	@warning Empty method body.
void Enemy::update() {

}

///	Sets the sprite for the enemy to have. By converting the int to an enum from spritesheet.
///	@param _j unique ID for the 10 enemy sprites.
void Enemy::setSprite(uint8_t _j) {
	switch (_j) {
	case 0:
		sprite[0] = spritesheet->enemy1;
		sprite[1] = spritesheet->enemy2;
		break;
	case 1:
		sprite[0] = spritesheet->enemy3;
		sprite[1] = spritesheet->enemy4;
		break;
	case 2:
		sprite[0] = spritesheet->enemy5;
		sprite[1] = spritesheet->enemy6;
		break;
	case 3:
		sprite[0] = spritesheet->enemy7;
		sprite[1] = spritesheet->enemy8;
		break;
	case 4:
		sprite[0] = spritesheet->enemy9;
		sprite[1] = spritesheet->enemy10;
		break;
	default:
		cout << "NO ENEMY SPRITES IN ENUM" << std::endl;
	}
}

///	Moves the enemy to the left.
void Enemy::moveLeft() {
	rect.x -= movementSpeed;
}

///	Moves the enemy to the right.
void Enemy::moveRight() {
	rect.x += movementSpeed;
}

void Enemy::moveDown() {
	rect.y += 64;
}

///	Sets the postion, width, height and enemy to alive.
///	@param _rect holds the sprite postion and dimensions.
///	@param _left sets which side the spaceship should begin on.
///	@param _spritesheet This is a reference to the spritesheet which will draw to the screen.
Spaceship::Spaceship(SDL_Rect _rect, bool _left, Spritesheet* _spritesheet) {
	spritesheet = _spritesheet;
	rect = _rect;
	left = _left;
	rect.w = width = 64;
	rect.h = height = 64;
	sprite = spritesheet->spaceShip;
	alive = true;
}

///	Sets all pointers to NULL;
Spaceship::~Spaceship() {
	spritesheet = NULL;
}

///	Draws the space ship on the screen.
void Spaceship::draw() {
	if (alive)spritesheet->draw(sprite, &rect);
}

///	@warning Method body is empty.
void Spaceship::update() {

}

///	Moves the ship either left or right. 
void Spaceship::movement() {
	if (left) {
		rect.x -= 1;
		if (rect.x <= 0) {
			rect.x = 0;
			alive = false;
			Spaceship::~Spaceship();
		}
	}
	else if (!left) {
		rect.x += 1;
		if (rect.x >= 464) {
			rect.x = 464;
			alive = false;
			Spaceship::~Spaceship();
		}
	}
}