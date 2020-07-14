#include "bullet.h"

///	Sets the bullet manager values.
/// @param _player reference to so player position can be called.
///	@param _spritesheet This is a reference to the spritesheet which will draw to the screen.
BulletManager::BulletManager(Player* _player, Spritesheet* _spritesheet) {
	player = _player;
	spritesheet = _spritesheet;
	increment = 0;
	bulletsOnScreen = 10;
}

///	Sets all the pointers to NULL.
BulletManager::~BulletManager() {
	for (int i = 0; i < 10; i++)
	{
		delete bullets[i];
		bullets[i] = NULL;
	}
	spritesheet = NULL;
	player = NULL;
}

///	Shoots a bullet from the players current position when called.
void BulletManager::shoot() {
	shooting = true;
	bullets[increment] = new Bullet(player->GetxPos(), spritesheet);
	increment++;
	if (increment >= bulletsOnScreen) increment = 0;
}

///	Draws all the bullets to the screen.
void BulletManager::draw() {
	if (isShooting()) {
		for (uint8_t i = 0; i < bulletsOnScreen; i++)
		{
			if (bullets[i] != NULL) bullets[i]->draw();
		}
	}
}

///	Updates all the bullets on screen position. 
void BulletManager::update() {
	if (isShooting()) {
		for (uint8_t i = 0; i < bulletsOnScreen; i++)
		{
			if (bullets[i] != NULL) {
				bullets[i]->update();
				if (bullets[i]->getYpos() <= 0) {
					delete bullets[i];
					bullets[i] = NULL;
				}
			}
		}
	}
}

void BulletManager::deleteBullet(int _x) {
	delete bullets[_x];
	bullets[_x] = NULL;
}

///	Getter for wether or no shooting is occuring.
///	@return shooting true or false.
bool BulletManager::isShooting() {
	return shooting;
}

///	Creates a bullet on the player current position and sets the speed.
Bullet::Bullet(uint16_t _xPos, Spritesheet* _spritesheet) {
	spritesheet = _spritesheet;
	xPos = _xPos+4;
	yPos = 782;
	bulletSpeed = 10;
	texture = spritesheet->playerBullet;
}

///	Sets all the pointers to NULL.
///	@warning If deleting the spritesheet, error on bullets destroy.
Bullet::~Bullet() {
	spritesheet = NULL;
	xPos = NULL;
	yPos = NULL;
	shooting = false;
	bulletSpeed = NULL;
	texture = NULL;
	pos = { NULL, NULL, NULL, NULL };

}

///	Moves the bullet along the y-axis.
void Bullet::update() {
	yPos -= bulletSpeed;
	if (yPos < 0) {
		yPos = 0;
	}
	pos = { xPos, yPos, 64, 64 };
}

///	Draws the bullet to the screen.
void Bullet::draw() {
	if(yPos > 0) spritesheet->draw(texture, &pos);
}
