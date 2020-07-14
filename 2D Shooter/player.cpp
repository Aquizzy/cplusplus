#include <iostream>

#include "player.h"

///	Sets all the players value; health, movement speedm width, height, postion.
///	@param	_ui reference to the UI so the player can update it as they get hurt or score points.
///	@param _spritesheet	This is a reference to the spritesheet which will draw to the screen.
Player::Player(UI* _ui, Spritesheet* _spritesheet, MenuManager* _menumanager, Gameloop* _gameloop) {
	health = 5;
	lives = 3;
	gameOver = false;
	movementSpeed = 10;
	width = height = 64;

	rect = { xPos, yPos, width, height };

	ui = _ui;
	spritesheet = _spritesheet;
	menuManager = _menumanager;
	gameloop = _gameloop;

	ui->health(health);
	ui->lives(lives);
}

///	Sets all the pointers to NULL.
Player::~Player() {
	spritesheet = NULL;
	ui = NULL;
}

///	@warning Empty method body.
void Player::update() {
}

///	Draws the player on the screen.
void Player::draw() {
	spritesheet->draw(spritesheet->playerShip, &rect);
}

///	Moves the player to the left or right depending on key press.
///	@param _x the amount of pixels to move per key press.
void Player::playerMovement(int16_t _x) {
	xPos += movementSpeed * _x;
	if (xPos <= width/2) xPos = width/2;
	if (xPos >= WIDTH-(2*width)) xPos = WIDTH - (2 * width);
	rect = { xPos, yPos, width, height };
}

///	Loses the player health and updates the UI. If health is 0 game over.
///	@param _damageAmount the amount of damage the player recieves.
void Player::loseHealth(uint8_t _damageAmount) {
	health -= _damageAmount;
	//ui->health(0);
	if (health <= 0 && !lives <= 0) {
		loseLife(1);
		health = 5;
	}
	if (health <= 0 && lives <= 0) {
		ui->lives(0);
		ui->health(0);
		gameloop->setGameOver();
		menuManager->currentMenu = menuManager->hiscores;
	}
	ui->health(health);
}

void Player::loseLife(uint8_t _livesLost) {
	lives -= _livesLost;
	ui->lives(lives);
}