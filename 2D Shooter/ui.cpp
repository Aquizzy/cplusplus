#include "ui.h"

UI::UI(SDL_Renderer* _renderer, Spritesheet* _spritesheet) {
	playerHealth = 5;
	score = 0;
	wave = 1;
	renderer = _renderer;
	spritesheet = _spritesheet;

	xPosHealth = 50;
	yPosHealth = 50;
	healthWidth = 64;
	healthHeight = 32;

	livesSprite[0] = { 232,50,32,32 };
	livesSprite[1] = { 257,50,32,32 };
	livesSprite[2] = { 282,50,32,32 };

	healthPos = { xPosHealth,yPosHealth, healthWidth, healthHeight };
}

UI::~UI() {
	spritesheet = NULL;
	renderer = NULL;
}

void UI::health(uint8_t _playerHealth) {
	playerHealth = _playerHealth;
}

void UI::lives(uint8_t _playerLives) {
	playerLives = _playerLives;
}

void UI::draw() {
	///	player health 5 gets the lowest image so it shows as 0 health.
	spritesheet->drawUiBorder();
	if (playerHealth <= 0) playerHealth = 0;
	switch (playerHealth) {
	case 5:
		spritesheet->drawHealth(0, &healthPos);
		break;
	case 4:
		spritesheet->drawHealth(1, &healthPos);
		break;
	case 3:
		spritesheet->drawHealth(2, &healthPos);
		break;
	case 2:
		spritesheet->drawHealth(3, &healthPos);
		break;
	case 1:
		spritesheet->drawHealth(4, &healthPos);
		break;
	case 0:
		spritesheet->drawHealth(5, &healthPos);
		break;

	}

	if (playerLives == 3) {
		spritesheet->drawUi(spritesheet->playerShip, &livesSprite[0]);
		spritesheet->drawUi(spritesheet->playerShip, &livesSprite[1]);
		spritesheet->drawUi(spritesheet->playerShip, &livesSprite[2]);
	}
	if (playerLives == 2) {
		spritesheet->drawUi(spritesheet->playerShip, &livesSprite[0]);
		spritesheet->drawUi(spritesheet->playerShip, &livesSprite[1]);
		spritesheet->drawUi(spritesheet->playerShipPlaceholder, &livesSprite[2]);
	}
	if (playerLives == 1) {
		spritesheet->drawUi(spritesheet->playerShip, &livesSprite[0]);
		spritesheet->drawUi(spritesheet->playerShipPlaceholder, &livesSprite[1]);
		spritesheet->drawUi(spritesheet->playerShipPlaceholder, &livesSprite[2]);
	}
	if (playerLives == 0) {
		spritesheet->drawUi(spritesheet->playerShipPlaceholder, &livesSprite[0]);
		spritesheet->drawUi(spritesheet->playerShipPlaceholder, &livesSprite[1]);
		spritesheet->drawUi(spritesheet->playerShipPlaceholder, &livesSprite[2]);
	}


	// drawFont(scoreText.data(), 25, 25, 34);
	scoreText = "SCORE: " + std::to_string(score);
	drawFont(scoreText.data(), 400, 38, 15);
	waveText = "WAVE: " + std::to_string(wave);
	drawFont(waveText.data() , 411, 58, 15);
	drawFont("HEALTH", 53, 29, 15);
	drawFont("LIVES", 253, 29, 15);
}

void UI::drawFont(const char* _msg, int _x, int _y, int _size) {
	SDL_Surface* surface;
	SDL_Texture* texture;
	TTF_Font* font = TTF_OpenFont("fonts/arial.ttf", _size);
	if (font == NULL) cout << "UI drawFont error: " << TTF_GetError();
	SDL_Color color;
	color.r = 154;
	color.g = 217;
	color.b = 65;
	color.a = 255;

	SDL_Rect rect;
	surface = TTF_RenderText_Solid(font, _msg, color);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	rect.x = _x;
	rect.y = _y;
	rect.h = surface->h;
	rect.w = surface->w;

	SDL_FreeSurface(surface);
	SDL_RenderCopy(renderer, texture, 0, &rect);
	SDL_DestroyTexture(texture);
	TTF_CloseFont(font);
}